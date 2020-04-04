#include <array>
#include <cstdio>
#include <iostream>
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

            bool loadCartridge(std::string filename)
            {
                m_cartridge = Cartridge::Cartridge(filename);
                return true;
            }

            bool setByte(size_t addr, uint8_t byte)
            {
                // Bootrom code writes a 1 to 0xFF50 to disable the ROM chip
                if (m_readFromBootrom && addr == 0xFF50 && byte) {
                    std::cout << "Disabling bootrom\n";
                    m_readFromBootrom = false;
                    return true;
                }
                if (addr < 0x8000)
                {
                    // std::cout << "Writing to cartridge\n";
                    m_cartridge.setByte(addr, byte);
                    return true;
                }

                if (addr < 0xA000)
                {
                    // std::cout << "Writing to VRAM\n";
                    m_vram[addr % 0x2000] = byte;
                    return true;
                }

                if (addr >= 0xA000 && addr < 0xC000) {
                    // std::cout << "Writing cartridge\n";
                    m_cartridge.setByte(addr, byte);
                    return true;
                }
                if (addr >= 0xC000 && addr < 0xE000) {
                    // std::cout << "Writing to ram\n";
                    m_lowram[addr % 0x2000] = byte;
                    return true;
                }
                if (addr >= 0xFE00 && addr < 0xFEA0) {
                    // std::cout << "Writing to OAM\n";
                    m_oam[addr % 0xA0] = byte;
                    return true;
                }

                if (addr >= 0xFF00 && addr < 0xFF80) {
                    // std::cout << "Writing to IO Ports\n";
                    uint8_t index = addr % 0x80;
                    m_ioports[index] = byte;
                    return true;
                }

                if (addr >= 0xFF80 && addr < 0xFFFF) {
                    // std::cout << "Writing to high ram\n";
                    m_highram[addr % 0x7F] = byte;
                    return true;
                }

                return false;
            }

            std::optional<uint8_t> readByte(size_t addr)
            {
                if (m_readFromBootrom && addr < 0x100) {
                    // std::cout << "Reading from bootrom\n";
                    return m_bootrom[addr];
                }
                if (addr >= 0x0 && addr < 0x8000) {
                    // std::cout << "Reading from cartridge\n";
                    return m_cartridge.readByte(addr);
                }
                if (addr >= 0x8000 && addr < 0xA000) {
                    // std::cout << "Reading from vram\n";
                    return m_vram[addr % 0x2000];
                }

                if (addr >= 0xA000 && addr < 0xC000) {
                    // std::cout << "Reading from cartridge\n";
                    return m_cartridge.readByte(addr);
                }
                if (addr >= 0xC000 && addr < 0xE000) {
                    // std::cout << "Reading from ram\n";
                    return m_lowram[addr % 0x2000];
                }
                if (addr >= 0xFE00 && addr < 0xFEA0) {
                    // std::cout << "Reading from OAM\n";
                    return m_oam[addr % 0xA0];
                }

                if (addr >= 0xFF00 && addr < 0xFF80) {
                    // std::cout << "Reading IO Ports\n";
                    return m_ioports[addr % 0x80];
                }
                if (addr >= 0xFF80 && addr < 0xFFFF) {
                    // std::cout << "Reading from high ram\n";
                    return m_highram[addr % 0x7F];
                }

                return {};
            }

            bool m_readFromBootrom;
            std::array<uint8_t, 0x100> m_bootrom;
            Cartridge::Cartridge m_cartridge;
            std::array<uint8_t, 0x2000> m_vram;
            std::array<uint8_t, 0x2000> m_lowram;
            std::array<uint8_t, 0xA0> m_oam;
            std::array<uint8_t, 0x80> m_ioports;            
            std::array<uint8_t, 0x7F> m_highram;
            

    };
    export MMU;
}