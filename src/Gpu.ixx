#include <array>
#include <cstdint>
#include <experimental/coroutine>
#include <experimental/generator>
#include <iostream>
#include <memory>
#include <optional>
#include <SDL.h>

export module Gpu;
import MMU;

namespace Gpu
{
    struct State
    {
        bool enabled { false };
        std::experimental::generator<bool> task;
    };

    struct Tile
    {
        std::array<std::array<uint8_t, 8>, 8> data;
    };

    std::array<uint8_t, 4> colours { 255, 192, 96, 0};

    class Gpu
    {
    public:
        Gpu(std::shared_ptr<MMU::MMU> mmu, SDL_Renderer* renderer): m_mmu(mmu), m_renderer(renderer)
        {
        }

        bool step()
        {
            bool enabledBit = isEnabled();
            if (!enabledBit) {
                m_state.enabled = false;
                return false;
            }

            if (!m_state.enabled && enabledBit) {
                reset();
                m_state.enabled = true;
            }

            if (m_state.enabled) {
                return *(m_state.task.begin());
            }
            return false;
        }

    private:

        void getTile(uint16_t address, Tile& tile)
        {
            for(int i = 0; i < 8; i++) {
                uint8_t lowRow = *(m_mmu->readByte(address + i*2));
                uint8_t highRow = *(m_mmu->readByte((address+1) + i*2));
                for(int j = 0; j < 8; j++) {
                   uint8_t highBit = (highRow & (1 << (7-j))) >> (7-j);
                   uint8_t lowBit = (lowRow & (1 << (7-j))) >> (7-j);

                   tile.data[i][j] = (highBit << 1) | lowBit;
                }
            }
        }

        void setMode(uint8_t mode)
        {
            uint8_t lcdcStatus = *(m_mmu->readByte(0xFF41));
            uint8_t status = (lcdcStatus & 0b11111100) | (mode & 0b11);
            m_mmu->setByte(0xFF41, status);
        }

        void renderScanLine(uint8_t y)
        {
            uint8_t lcdControl = *(m_mmu->readByte(0xFF40));
            uint8_t bgMapSelect = (lcdControl>>3) & 1;
            uint8_t bgTileMode = (lcdControl >> 4) & 1;
            uint16_t bgMapBase = bgMapSelect ? 0x9C00 : 0x9800;
            uint16_t bgTileBase = bgTileMode ? 0x8000: 0x9000;
            uint8_t scy = *(m_mmu->readByte(0xFF42));
            uint8_t scx = *(m_mmu->readByte(0xFF43));

            // Since tiles are 8x8, remove the bottom 3 bits to get the tile index
            // Bottom 3 bits are the offset within the tile
            uint8_t tileYIndex = (scy + y) >> 3;
            uint8_t tileXIndex = (scx) >> 3;
            uint16_t tileAddress = bgMapBase + (32 * tileYIndex) + tileXIndex;
            uint8_t tileNum = *(m_mmu->readByte(tileAddress));

            uint16_t tileDataAddress = bgTileBase + (16 * tileNum);
            Tile tile;
            getTile(tileDataAddress, tile);

            uint8_t bgp = *(m_mmu->readByte(0xFF47));
            std::array<uint8_t, 4> shades = {
                colours[bgp & 0b11],
                colours[(bgp >> 2) & 0b11],
                colours[(bgp >> 4) & 0b11],
                colours[(bgp >> 6) & 0b11],
            };

            uint8_t tileYOffset = (scy + y) & 0b111;
            uint8_t tileXOffset = (scx) & 0b111;

            for(int i = 0; i < 160; i++) {
                uint8_t pixelColour = tile.data[tileYOffset][tileXOffset];
                SDL_SetRenderDrawColor(m_renderer, shades[pixelColour],shades[pixelColour],shades[pixelColour], 255);
                SDL_RenderDrawPoint(m_renderer, i, y);
                
                tileXOffset++;
                if (tileXOffset == 8) {
                    tileXOffset = 0;
                    tileXIndex = (tileXIndex + 1) & 0x1F; // Wrap around if passed 32
                    tileAddress = bgMapBase + (32 * tileYIndex) + tileXIndex;
                    tileNum = *(m_mmu->readByte(tileAddress));

                    tileDataAddress = bgTileBase + (16 * tileNum);
                    getTile(tileDataAddress, tile);
                }
            }
        }

        std::experimental::generator<bool> createTask()
        {
            bool toggle = true;
            while(true)
            {
                for (uint8_t y = 0; y < 144; y++) {
                    uint8_t lcdcStatus = *(m_mmu->readByte(0xFF41));
                    uint8_t scx;
                    uint8_t scy;
                    
                    // Update LY value
                    m_mmu->setByte(0xFF44, y);

                    setMode(2);
                    // Mode 2, OAM
                    // std::cout << "GPU MODE 2\n";
                    for (int i = 0; i < 80; i++) {
                        co_yield true;
                    }
                    
                    setMode(3);
                    // Mode 3, VRAM
                    // std::cout << "GPU MODE 3\n";
                    for (int i = 0; i < 172; i++) {
                        co_yield true;
                    }

                    // Mode 0, HBLANK
                    setMode(0);
                    renderScanLine(y);
                    
                    for (int i = 0; i < 204; i++) {
                        co_yield true;
                    }
                }

                // VBLANK
                setMode(1);             
                SDL_RenderPresent(m_renderer);
                for (uint8_t y = 144; y < 154; y++)
                {
                    m_mmu->setByte(0xFF44, y);
                    for(int i = 0; i < 456;i ++) {
                        co_yield true;
                    }
                    
                }
            }
        }

        bool isEnabled()
        {
            uint8_t controlRegister = *(m_mmu->readByte(0xFF40));
            return controlRegister & (1 << 7);
        }

        void reset()
        {
            m_state.task = createTask();
        }   

        std::shared_ptr<MMU::MMU> m_mmu;
        SDL_Renderer* m_renderer;
        State m_state;
    };

    export Gpu;
}