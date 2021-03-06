#include <array>
#include <experimental/coroutine>
#include <experimental/generator>
#include <functional>
#include <iostream>
#include <memory>

export module Instructions;

import MMU;
import Registers;

namespace Cpu
{
struct Instruction
	{
		Instruction() : 
			opcode(0), 
			name("UNIMPLEMENTED"), 
			numParams(0), 
			command([](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
				std::cout << "This instruction is not implemented\n";
				co_yield(false);
			}) 
		{}
		Instruction(uint8_t op, 
					const char* name, 
					uint8_t numParams, 
					std::function<std::experimental::generator<bool>(const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr)> command) 
			: 
			opcode(op), 
			name(name), 
			numParams(numParams), 
			command(command) {};
		uint8_t opcode;
		const char* name;
		uint8_t numParams;
		std::function<std::experimental::generator<bool>(const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr)> command;
	};
export Instruction;

uint8_t EightBitSubtract(Cpu::Registers& reg, uint8_t val1, uint8_t val2, bool carry)
{
    uint8_t carryBit = carry ? 1 : 0;
    uint16_t sum = val1 - val2 - carryBit;
    uint16_t halfSum = (val1 & 0xF) - (val2 & 0xF) - carryBit;
    reg.Zero((sum & 0xFF) == 0);
    reg.Sub(true);
    reg.HalfCarry(halfSum > 0xF);
    reg.Carry(sum > 0xFF);

    return sum;
}

uint8_t EightBitAdd(Cpu::Registers& reg, uint8_t val1, uint8_t val2, bool carry)
{
    uint8_t carryBit = carry ? 1 : 0;
    uint16_t sum = val1 + val2 + carryBit;
    uint16_t halfSum = (val1 & 0XF) + (val2 & 0xF) + carry;
    reg.Zero((sum & 0xFF) == 0);
    reg.Sub(false);
    reg.HalfCarry(halfSum > 0xF);
    reg.Carry(sum > 0xFF);
    return sum & 0xFF;
}

uint8_t EightBitDecrement(Cpu::Registers& reg, uint8_t value)
{
    reg.Zero(value == 0x01);
    reg.Sub(true);
    reg.HalfCarry((value & 0xF) == 0x0);
    return value-1;
}

uint8_t EightBitIncrement(Cpu::Registers& reg, uint8_t value) 
{
    reg.Zero(value == 0xFF);
    reg.Sub(false);
    reg.HalfCarry((value & 0xF) == 0xF);
    return value + 1;
}

export std::array<Instruction, 0x100> instructions = {
		Instruction{0x00, "nop", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
				co_yield true;
				co_yield true;
				co_yield true;
				co_yield false;
			}
		},
        Instruction{0x01, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x02, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x03, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x04, "INC B", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.B = EightBitIncrement(reg, reg.B);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x05, "DEC B", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "Decrementing B to " << std::hex << +(reg.B-1) <<"\n";
                

                reg.Zero(reg.B == 1);
                reg.Sub(true);
                reg.HalfCarry((reg.B & 0xF) == 0);
                reg.B--;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x06, "LD B,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                // std::cout << "Setting B to " << std::hex << +byte << "\n";
                reg.B = byte;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x07, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x08, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x09, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x0A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x0B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x0C, "INC C", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.HalfCarry((reg.C & 0xFF) == 0xFF);

                reg.C++;
                reg.Sub(false);
                reg.Zero(reg.C == 0);

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x0D, "DEC C", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                  reg.C= EightBitDecrement(reg, reg.C);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x0E, "LD C", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                reg.C = byte;
                //std::cout << "Setting C to " << std::hex << +byte << "\n";
               
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x0F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x10, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x11, "LD DE,u16", 2, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto lowRead = mmu->readByte(addr+1);
                if (!lowRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t low = *lowRead;
                reg.E = low;
                // std::cout << "Setting E to " << std::hex << +low << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto highRead = mmu->readByte(addr+2);
                if (!highRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+2 << "\n";
                }
                uint8_t high = *highRead;
                reg.D = high;
                // std::cout << "Setting D to " << std::hex << +high << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;


                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x12, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x13, "INC DE", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "Incrementing DE\n";
                reg.DE(reg.DE() + 1);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x14, "INC D", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.D = EightBitIncrement(reg, reg.D);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x15, "DEC D", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.D= EightBitDecrement(reg, reg.D);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x16, "LD D,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                // std::cout << "Setting B to " << std::hex << +byte << "\n";
                reg.D = byte;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x17, "RLA", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                bool carry = reg.Carry();
                reg.Zero(false);
                reg.Sub(false);
                reg.HalfCarry(false);
                reg.Carry(reg.A & 0x80);
                // std::cout << "Setting flags to " << std::hex << +reg.F << "\n";
                // std::cout << "Setting A ( " << std::hex << +reg.A << ") to ";
                reg.A = (reg.A << 1) | (carry ? 1 : 0);
                // std::cout << std::hex << +reg.A << "\n";

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x18, "JR i8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto readResult = mmu->readByte(addr+1);
                int8_t value = static_cast<int8_t>(*readResult);
                // std::cout << "Jump offset: " << static_cast<int16_t>(value) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;
                
                reg.PC += value;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
                
            }
        },
        Instruction{0x19, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1A, "LD A,(DE)", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto readResult = mmu->readByte(reg.DE());
                // std::cout << "Reading memory at " << std::hex << reg.DE() << "\n";
                if (!readResult) {
                    std::cout << "Error reading memory at " << std::hex << +reg.DE() << "\n";
                } 
                reg.A = *readResult;
                // std::cout << "Setting A to " << std::hex << +(*readResult) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x1B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1D, "DEC E", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                 reg.E = EightBitDecrement(reg, reg.E);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x1E, "LD E,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                reg.E = byte;
                //std::cout << "Setting E to " << std::hex << +byte << "\n";
               
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x1F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x20, "JR NZ", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto readResult = mmu->readByte(addr+1);
                int8_t value = static_cast<int8_t>(*readResult);
                // std::cout << "Jump offset: " << static_cast<int16_t>(value) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;
                if (reg.Zero()) {
                    // std::cout << "Zero, not jumping\n";
                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield false;
                }
                else {
                    // std::cout << "Not Zero, PC=" << std::hex << +reg.PC << "\n";
                    reg.PC += value;

                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield true;

                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield false;
                }

               
            }
        },
        Instruction{0x21, "LD HL,rr", 2, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto lowRead = mmu->readByte(addr+1);
                if (!lowRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t low = *lowRead;
                reg.L = low;
                //std::cout << "Setting L to " << std::hex << +low << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto highRead = mmu->readByte(addr+2);
                if (!highRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+2 << "\n";
                }
                uint8_t high = *highRead;
                reg.H = high;
                //std::cout << "Setting H to " << std::hex << +high << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;


                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x22, "LD (HL+), A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "Writing A (" << std::hex << +reg.A << ") to (HL) (" << reg.HL() << ")\n";
                mmu->setByte(reg.HL(), reg.A);

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                // std::cout << "Incrementing HL\n";
                reg.HL(reg.HL()+1);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x23, "INC HL", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "Incrementing HL\n";
                reg.HL(reg.HL()+1);
                 co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

               co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x24, "INC H", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.H = EightBitIncrement(reg, reg.H);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x25, "DEC H", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
               reg.H= EightBitDecrement(reg, reg.H);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x26, "LD H,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                // std::cout << "Setting B to " << std::hex << +byte << "\n";
                reg.H = byte;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x27, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x28, "JRZ,i8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
               auto readResult = mmu->readByte(addr+1);
                int8_t value = static_cast<int8_t>(*readResult);
                // std::cout << "Jump offset: " << static_cast<int16_t>(value) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;
                if (!reg.Zero()) {
                    // std::cout << "Not Zero, not jumping\n";
                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield false;
                }
                else {
                    // std::cout << "Not Zero, PC=" << std::hex << +reg.PC << "\n";
                    reg.PC += value;

                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield true;

                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield false;
                }
            }
        },
        Instruction{0x29, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2D, "DEC L", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                 reg.L = EightBitDecrement(reg, reg.L);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x2E, "LD L,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                reg.L = byte;
                //std::cout << "Setting L to " << std::hex << +byte << "\n";
               
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x2F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x30, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x31, "LD SP,nn", 2, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {                
                auto lowRead = mmu->readByte(addr+1);
                if (!lowRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t low = *lowRead;
                reg.setSP(0, low);
                //std::cout << "Setting SP to " << std::hex << +low << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto highRead = mmu->readByte(addr+2);
                if (!highRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+2 << "\n";
                }
                uint8_t high = *highRead;
                reg.setSP(high, low);
                //std::cout << "Setting SP to " << std::hex << +((high << 8) | low) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;


                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x32, "LD (HL-) A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                
                // std::cout << "Setting memory location " << std::hex << reg.HL() << " to " << std::hex << +reg.A << "\n";
                // std::cout << "Setting HL to " << std::hex << reg.HL()-1 << "\n";
                mmu->setByte(reg.HL(), reg.A);
                reg.HL(reg.HL()-1);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;


                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x33, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x34, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x35, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x36, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x37, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x38, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x39, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3D, "DEC A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitDecrement(reg, reg.A);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x3E, "LD A,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t byte = *byteRead;
                reg.A = byte;
                //std::cout << "Setting A to " << std::hex << +byte << "\n";
               
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            
            }
        },
        Instruction{0x3F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x40, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x41, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x42, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x43, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x44, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x45, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x46, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x47, "LD B,A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.B = reg.A;
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x48, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x49, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4F, "LD C,A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // C <- A
                // std::cout << "Set C to A (" << std::hex << +reg.A << ")\n";
                reg.C = reg.A;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x50, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x51, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x52, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x53, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x54, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x55, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x56, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x57, "LD D,A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.D = reg.A;
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x58, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x59, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x60, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x61, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x62, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x63, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x64, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x65, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x66, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x67, "LD H,A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.H = reg.A;
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x68, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x69, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x70, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x71, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x72, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x73, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x74, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x75, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x76, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x77, "LD (HL), A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                
                mmu->setByte(reg.HL(), reg.A);
                // std::cout << "Setting address " << std::hex << reg.HL() << " to " << +reg.A << "\n";

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0x78, "LD A,B", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                 reg.A = reg.B;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x79, "LD A,C", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = reg.B;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x7A, "LD A,D", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = reg.D;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x7B, "LD A,E", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "Setting A to E(" << std::hex << +reg.E << ")\n";
                reg.A = reg.E;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x7C, "LD A,H", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = reg.H;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x7D, "LD A,L", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = reg.L;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x7E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x80, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x81, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x82, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x83, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x84, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x85, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x86, "ADD A,(HL)", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(reg.HL());
                if (!byteRead) {
                    std::cout << "Error reading byte at HL(" << std::hex << reg.HL() << ")\n";
                }
                uint8_t val = *byteRead;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                reg.A = EightBitAdd(reg, reg.A, val, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x87, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x88, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x89, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x8A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x8B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x8C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x8D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x8E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x8F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x90, "SUB A,B", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitSubtract(reg, reg.A, reg.B, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x91, "SUB A,C", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitSubtract(reg, reg.A, reg.C, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x92, "SUB A,D", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitSubtract(reg, reg.A, reg.D, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x93, "SUB A,E", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitSubtract(reg, reg.A, reg.E, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x94, "SUB A,H", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitSubtract(reg, reg.A, reg.H, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x95, "SUB A,L", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                reg.A = EightBitSubtract(reg, reg.A, reg.L, false);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0x96, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x97, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x98, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x99, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x9A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x9B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x9C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x9D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x9E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x9F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA0, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAD, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAF, "xor A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                co_yield true;
                co_yield true;
                co_yield true;
                reg.A ^= reg.A;

               co_yield false;
            }
        },
        Instruction{0xB0, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xB9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xBA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xBB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xBC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xBD, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xBE, "CP A,(HL)", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(reg.HL());
                if (!byteRead) {
                    std::cout << "Error reading byte at HL(" << std::hex << reg.HL() << ")\n";
                }
                uint8_t val = *byteRead;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                EightBitSubtract(reg, reg.A, val, false);
                
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xBF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC0, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC1, "POP BC", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "SP: " << reg.SP << "\n";
                reg.SP = reg.SP + 2;
                // std::cout << "Setting SP to " << std::hex << reg.SP << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto cRead = mmu->readByte(reg.SP-2);
                if (!cRead) {
                    std::cout << "Error reading memory at " << reg.SP-2 << "\n";
                }
                // std::cout << "Setting C to SP-2 (" << +(*cRead) << ")\n";

                reg.C = *cRead;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;
                
                
                auto bRead = mmu->readByte(reg.SP-1);
                if (!bRead) {
                    std::cout << "Error reading memory at " << reg.SP-1 << "\n";
                }
                // std::cout << "Setting B to SP-1 (" << +(*bRead) << ")\n";
                reg.B = *bRead;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xC2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC5, "PUSH BC", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                // std::cout << "SP: " << reg.SP << "\n";
                reg.SP = reg.SP - 2;
                // std::cout << "Setting SP to " << std::hex << reg.SP << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;
                
                // std::cout << "Setting SP+1 (" << std::hex << reg.SP+1 << ") to B (" << +reg.B << ")\n";
                mmu->setByte(reg.SP+1, reg.B);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                // std::cout << "Setting SP (" << std::hex << reg.SP << ") to C (" << +reg.C << ")\n";
                mmu->setByte(reg.SP, reg.C);
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xC6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC9, "RET", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto lowRead = mmu->readByte(reg.SP);
                if (!lowRead) {
                    std::cout << "Error reading memory at " << reg.SP << "\n";
                }
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto highRead = mmu->readByte(reg.SP+1);
                if (!highRead) {
                    std::cout << "Error reading memory at " << reg.SP+1 << "\n";
                }
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                reg.setPC(*highRead, *lowRead);
                // std::cout << "Returning to address " << std::hex << reg.PC << "\n";
                reg.SP += 2;
                // std::cout << "Setting SP to " << std::hex << reg.SP << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xCA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCB, "CB xx", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                //std::cout << std::hex << +(*(mmu->readByte(addr))) << " " << +(*(mmu->readByte(addr+1))) << "\n";
                uint8_t cbOpcode = *(mmu->readByte(addr+1));
                uint8_t const op = cbOpcode >> 6;
                uint8_t bitIndex = (cbOpcode >> 3) & 0b111;
                uint8_t regOperand = cbOpcode & 0b111;

                switch(op) {
                    case 0:
                        // shift & swap
                        switch (bitIndex) {
                            case 0:
                                // rlc rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                reg.Zero(value == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x80);

                                value = (value << 1) | (value >> 7);
                                reg.reg(mmu, regOperand, value);

                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 1:
                                // rrc rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                reg.Zero(value == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x01);

                                value = (value >> 1) | (value << 7);
                                reg.reg(mmu, regOperand, value);

                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 2:
                            // rl rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                uint8_t rotate = (value << 1) | (reg.Carry() ? 1 : 0);
                                reg.Zero(rotate == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x80);

                                reg.reg(mmu, regOperand, rotate);

                                // Reading from memory means more clock cycles
                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 3:
                            // rr rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                uint8_t rotate = (value >> 1) | (reg.Carry() ? 1 : 0);
                                reg.Zero(rotate == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x01);

                                reg.reg(mmu, regOperand, rotate);

                                // Reading from memory means more clock cycles
                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 4:
                            // sla rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                uint8_t shifted = value << 1;
                                reg.Zero(shifted == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x80);

                                reg.reg(mmu, regOperand, shifted);

                                // Reading from memory means more clock cycles
                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 5:
                            // sra rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                uint8_t shifted = (value >> 1) | (value & 0x80);
                                reg.Zero(shifted == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x01);

                                reg.reg(mmu, regOperand, shifted);

                                // Reading from memory means more clock cycles
                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 6:
                            // swap rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                value = (value >> 4) | (value << 4);
                                reg.Zero(value == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(false);

                                reg.reg(mmu, regOperand, value);

                                // Reading from memory means more clock cycles
                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                            case 7:
                            // srl rN
                            {
                                uint8_t value = reg.reg(mmu, regOperand);
                                uint8_t shifted = value >> 1;
                                reg.Zero(shifted == 0);
                                reg.Sub(false);
                                reg.HalfCarry(false);
                                reg.Carry(value & 0x01);

                                reg.reg(mmu, regOperand, shifted);
                                // Reading from memory means more clock cycles
                                uint8_t cycles = regOperand == 6 ? 12 : 8;
                                
                                for(int i = 0; i < cycles-1; i++) {
                                    co_yield true;
                                }
                                co_yield false;
                            }
                            break;
                        }
                    break;
                    case 1:
                    // bit n, rN
                    {
                        uint8_t value = reg.reg(mmu, regOperand);
                        reg.Zero((value & (1 << bitIndex)) == 0);
                        reg.Sub(false);
                        reg.HalfCarry(true);

                        // Reading from memory means more clock cycles
                        uint8_t cycles = regOperand == 6 ? 12 : 8;
                        
                        for(int i = 0; i < cycles-1; i++) {
                            co_yield true;
                        }
                        co_yield false;
                    }
                    break;
                    case 2:
                    // res n, rN
                    {
                        uint8_t value = reg.reg(mmu, regOperand);
                        reg.reg(mmu, regOperand, (value & ~(1 << bitIndex)));
                        // Reading from memory means more clock cycles
                        uint8_t cycles = regOperand == 6 ? 12 : 8;
                        
                        for(int i = 0; i < cycles-1; i++) {
                            co_yield true;
                        }
                        co_yield false;

                    }
                    break;
                    case 3:
                    // set n, rN
                    {
                        uint8_t value = reg.reg(mmu, regOperand);
                        reg.reg(mmu, regOperand, (value | (1 << bitIndex)));
                        // Reading from memory means more clock cycles
                        uint8_t cycles = regOperand == 6 ? 12 : 8;
                        
                        for(int i = 0; i < cycles-1; i++) {
                            co_yield true;
                        }
                        co_yield false;

                    }
                    break;
                }
            }
        },
        Instruction{0xCC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCD, "CALL nn", 2, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto lowRead = mmu->readByte(addr+1);
                if (!lowRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t low = *lowRead;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto highRead = mmu->readByte(addr+2);
                if (!highRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t high = *highRead;
                // std::cout << "Calling subroutine at " << std::hex << +high << +low << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                reg.SP = reg.SP - 2;
                // std::cout << "Setting SP to " << std::hex << reg.SP << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                uint8_t lowPC = reg.PC & 0xFF;
                uint8_t highPC = (reg.PC >> 8) & 0xFF;
                mmu->setByte(reg.SP + 1, highPC);
                // std::cout << "Writing " << std::hex << +highPC << " to " << +(reg.SP+1) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                mmu->setByte(reg.SP, lowPC);
                // std::cout << "Writing " << std::hex << +lowPC << " to " << +reg.SP << "\n";
                reg.setPC(high, low);
                // std::cout << "Setting PC to " << std::hex << +high << +low << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;

            }
        },
        Instruction{0xCE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD0, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xD9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xDA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xDB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xDC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xDD, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xDE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xDF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE0, "LD (FF00+u8),A", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Invalid read at " << std::hex << (addr+1) << "\n";
                }
                uint16_t address = 0xFF00 + *byteRead;
                // std::cout << "Read address " << std::hex << address << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                mmu->setByte(address, reg.A);
                // std::cout << "Set address " << std::hex << address << " to " << +reg.A << "\n";

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xE1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE2, "LD (FF00+C),A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                mmu->setByte(0xFF00 + reg.C, reg.A);
                // std::cout << "Writing to address " << std::hex << 0xFF00 + reg.C << " value " << +reg.A << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xE3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEA, "LD (u16), A", 2, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                 auto lowRead = mmu->readByte(addr+1);
                if (!lowRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+1 << "\n";
                }
                uint8_t low = *lowRead;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                auto highRead = mmu->readByte(addr+2);
                if (!highRead) {
                    std::cout << "Error reading memory at " << std::hex << +addr+2 << "\n";
                }
                uint8_t high = *highRead;
                
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                uint16_t address = (high << 8) | low;
                mmu->setByte(address, reg.A);
                // std::cout << "Setting address " << std::hex << address << " to A (" << +reg.A << ")\n";
                 co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                 co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xEB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xED, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF0, "LD A,(FF00+u8)", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
               auto byteRead = mmu->readByte(addr+1);
                if (!byteRead) {
                    std::cout << "Invalid read at " << std::hex << (addr+1) << "\n";
                }
                uint16_t address = 0xFF00 + *byteRead;
                // std::cout << "Read address " << std::hex << address << ": ";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                byteRead = mmu->readByte(address);
                if (!byteRead) {
                    std::cout << "Invalid read at " << std::hex << (address) << "\n";
                }
                reg.A = *byteRead;
                // std::cout << std::hex << +reg.A << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;

              
            }
        },
        Instruction{0xF1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xF9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xFA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xFB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xFC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xFD, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xFE, "CP A,u8", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto readResult = mmu->readByte(addr+1);
                if (!readResult) {
                    std::cout << "Error reading memory at address " << std::hex << addr+1 << "\n";
                }
                uint8_t val = *readResult;
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                EightBitSubtract(reg, reg.A, val, false);
                co_yield true;
                co_yield true;
                co_yield true;
               co_yield false;
            }
        },
        Instruction{0xFF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                std::cout << "UNIMPLEMENTED -ADDRESS " << std::hex << addr << "\n";
                exit(1);
               co_yield false;
            }
        },

	};
// export instructions;

}