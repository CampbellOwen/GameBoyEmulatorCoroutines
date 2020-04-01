

// includes
#include <array>
#include <cstdio>
#include <memory>
#include <optional>
#include <string>


export module Cartridge;


namespace Cartridge
{
    class Cartridge
    {
    public:
        Cartridge() = default;
        Cartridge(const std::string& filename) noexcept
        {
            std::unique_ptr<FILE, int(*)(FILE*)> spFile(fopen(filename.c_str(), "rb"), fclose);
            fread(bank0.data(), sizeof(uint8_t), 0x4000, spFile.get());
            fread(bank1.data(), sizeof(uint8_t), 0x4000, spFile.get());
        }
        std::optional<uint8_t> readByte(size_t addr)
        {
            if (addr > 0x7FFF) {
                return {};
            }

            if (addr > 0x3FFF) {
                return bank1[addr % 0x4000];
            }

            return bank0[addr];
        }
        bool setByte(size_t addr, uint8_t byte)
        {
            if (addr > 0x7FFF) {
                return false;
            }

            if (addr > 0x3FFF) {
                bank1[addr % 0x4000] = byte;
                return true;
            }

            bank0[addr] = byte;
            return true;
        }
    private:
        std::array<uint8_t, 0x4000> bank0;
        std::array<uint8_t, 0x4000> bank1;
    };
    export Cartridge;
}