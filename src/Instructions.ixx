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
                exit(1);
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x02, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x03, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x04, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x05, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x06, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x07, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x08, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x09, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x0A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x0B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
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
        Instruction{0x0D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
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
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x10, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
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
                std::cout << "Setting E to " << std::hex << +low << "\n";
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
                std::cout << "Setting D to " << std::hex << +high << "\n";
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
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x13, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x14, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x15, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x16, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x17, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x18, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x19, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1A, "LD A,(DE)", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto readResult = mmu->readByte(reg.DE());
                std::cout << "Reading memory at " << std::hex << reg.DE() << "\n";
                if (!readResult) {
                    std::cout << "Error reading memory at " << std::hex << +reg.DE() << "\n";
                } 
                reg.A = *readResult;
                std::cout << "Setting A to " << std::hex << +(*readResult) << "\n";
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
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x1F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x20, "JR NZ", 1, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                auto readResult = mmu->readByte(addr+1);
                int8_t value = static_cast<int8_t>(*readResult);
                //std::cout << "Jump offset: " << static_cast<int16_t>(value) << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;
                if (reg.Zero()) {
                    co_yield true;
                    co_yield true;
                    co_yield true;
                    co_yield false;
                }
                else {
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
        Instruction{0x22, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x23, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x24, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x25, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x26, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x27, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x28, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x29, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x2F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x30, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
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
                mmu->setByte(reg.HL(), reg.A);
                //std::cout << "Setting memory location " << std::hex << reg.HL() << " to " << std::hex << +reg.A << "\n";
                // std::cout << "Setting HL to " << std::hex << reg.HL()-1 << "\n";
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
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x34, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x35, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x36, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x37, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x38, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x39, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x3D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
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
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x40, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x41, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x42, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x43, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x44, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x45, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x46, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x47, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x48, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x49, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x4F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x50, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x51, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x52, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x53, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x54, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x55, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x56, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x57, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x58, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x59, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x60, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x61, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x62, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x63, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x64, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x65, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x66, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x67, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x68, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x69, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x6F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x70, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x71, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x72, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x73, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x74, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x75, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x76, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x77, "LD (HL), A", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                
                mmu->setByte(reg.HL(), reg.A);
                std::cout << "Setting address " << std::hex << reg.HL() << " to " << +reg.A << "\n";

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
        Instruction{0x78, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x79, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x7F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x80, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x81, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x52, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x53, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x54, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x55, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x56, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x57, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x58, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x59, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x50, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x51, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x52, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x53, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x54, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x55, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x56, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x57, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x58, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x59, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA0, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xA9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAD, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xAE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
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
        Instruction{0x50, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x51, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x52, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x53, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x54, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x55, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x56, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x57, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x58, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x59, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC0, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC1, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC2, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC3, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xC9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
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
                                uint8_t rotate = (value << 1) | (reg.C ? 1 : 0);
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
                                uint8_t rotate = (value >> 1) | (reg.C ? 1 : 0);
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
                
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield false;
            }
        },
        Instruction{0xCC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCD, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xCF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x50, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x51, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x52, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x53, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x54, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x55, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x56, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x57, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x58, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x59, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5A, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5B, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5C, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5D, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5E, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0x5F, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
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
                std::cout << "Read address " << std::hex << address << "\n";
                co_yield true;
                co_yield true;
                co_yield true;
                co_yield true;

                mmu->setByte(address, reg.A);
                std::cout << "Set address " << std::hex << address << " to " << +reg.A << "\n";

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
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE4, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE5, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE6, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE7, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE8, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xE9, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEA, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEB, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEC, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xED, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEE, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },
        Instruction{0xEF, "UNIMPLEMENTED", 0, 
			[](const std::shared_ptr<MMU::MMU>& mmu, Cpu::Registers& reg, uint16_t addr) -> std::experimental::generator<bool> {
                exit(1);
               co_yield false;
            }
        },

	};
// export instructions;

}