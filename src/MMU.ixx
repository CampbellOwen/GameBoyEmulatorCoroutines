#include <array>
#include <memory>
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

            }

            bool loadCartridge(const std::string& filename)
            {
                m_cartridge = Cartridge::Cartridge(filename);
            }

            bool setByte(size_t addr, uint8_t byte)
            {
                if (m_readFromBootrom && addr == 0xFF50) {
                    m_readFromBootrom = false;
                    return true;
                }
                if (addr < 0x8000)
                {
                    m_cartridge.setByte(addr, byte);
                    return true;
                }

                if (addr < 0xC000)
                {
                    m_vram[addr % 0x2000] = byte;
                    return true;
                }

                return false;
            }

            bool m_readFromBootrom;
            std::array<uint8_t, 0x1FFF> m_vram;
            Cartridge::Cartridge m_cartridge;
            std::array<uint8_t, 0xFF> m_bootrom;
            

    };
    export MMU;
}