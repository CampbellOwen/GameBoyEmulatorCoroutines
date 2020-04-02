#include <array>
#include <cstdio>
#include <memory>
#include <optional>
#include <string>

export module MMU;

import Cartridge;

namespace MMU
{
    class MMU
    {
        public:
            MMU(const std::string& bootRomPath): m_readFromBootrom(true) 
            {
                std::unique_ptr<FILE, int(*)(FILE*)> spFile(fopen(bootRomPath.c_str(), "rb"), fclose);
                fread(m_bootrom.data(), sizeof(uint8_t), 0x100, spFile.get());
            }

            bool loadCartridge(std::shared_ptr<Cartridge::Cartridge> spCartridge)
            {
                m_spCartridge = spCartridge;
                return true;
            }

            bool setByte(size_t addr, uint8_t byte)
            {
                // Bootrom code writes a 1 to 0xFF50 to disable the ROM chip
                if (m_readFromBootrom && addr == 0xFF50 && byte) {
                    m_readFromBootrom = false;
                    return true;
                }
                if (addr < 0x8000)
                {
                    m_spCartridge->setByte(addr, byte);
                    return true;
                }

                if (addr < 0xC000)
                {
                    m_vram[addr % 0x2000] = byte;
                    return true;
                }

                return false;
            }

            std::optional<uint8_t> readByte(size_t addr)
            {
                if (m_readFromBootrom && addr < 0x100) {
                    return m_bootrom[addr];
                }
                if (addr < 0x8000) {
                    return m_spCartridge->readByte(addr);
                }
                if (addr < 0xC000) {
                    return m_vram[addr % 0x2000];
                }

                return {};
            }

            bool m_readFromBootrom;
            std::array<uint8_t, 0x200> m_vram;
            std::shared_ptr<Cartridge::Cartridge> m_spCartridge;
            std::array<uint8_t, 0x100> m_bootrom;
            

    };
    export MMU;
}