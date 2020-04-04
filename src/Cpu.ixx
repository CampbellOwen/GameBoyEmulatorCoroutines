#include <array>
#include <cstdint>
#include <experimental/coroutine>
#include <experimental/generator>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>

export module Cpu;

import Registers;
import MMU;
import Instructions;


namespace Cpu
{
	struct State
	{
		State() : currCommand({}), currInstruction(instructions[0]), executing(false) {};
		std::optional<std::experimental::generator<bool> > currCommand;
		Instruction& currInstruction;
		bool executing { false };
		bool log { false };
	};

	class Cpu
	{
		public:


			bool step()
			{
				if (!m_state.executing)
				{
					uint16_t addr = m_reg.PC;
					
					if (m_state.log) {
						std::cout << "[" << std::hex << std::setfill('0') << std::setw(4) << addr << "] ";
					}
					auto opcodeResult = m_mmu->readByte(addr);
					uint8_t opcode;
					if (opcodeResult) {
						opcode = *opcodeResult;
					}
					else {
						std::cout << "Invalid opcode\n";
						return false;
					}
					if (m_state.log) {
						std::cout << "[" << std::hex << std::setfill('0') << std::setw(2) << +opcode << "] - ";
					}
					Instruction& currInst = instructions[opcode];
					if (m_state.log) {
						std::cout << currInst.name << "\n";
					}

					m_state.currCommand = currInst.command(m_mmu, m_reg, addr);
					m_state.currInstruction = currInst;

					m_reg.PC += currInst.numParams + 1;

				}

				m_state.executing = *(m_state.currCommand->begin());


				return true;
			}

			Cpu(std::shared_ptr<MMU::MMU> mmu): m_mmu(mmu)
			{
			}

			void dumpRegisters()
			{
				std::cout << "A: " << std::hex << +m_reg.A << "\n";
				std::cout << "B: " << std::hex << +m_reg.B << "\n";
				std::cout << "C: " << std::hex << +m_reg.C << "\n";
				std::cout << "D: " << std::hex << +m_reg.D << "\n";
				std::cout << "E: " << std::hex << +m_reg.E << "\n";
				std::cout << "F: " << std::hex << +m_reg.F << "\n";
				std::cout << "H: " << std::hex << +m_reg.H << "\n";
				std::cout << "L: " << std::hex << +m_reg.L << "\n";
				std::cout << "SP: " << std::hex << +m_reg.SP << "\n";
				std::cout << "PC: " << std::hex << +m_reg.PC << "\n";
			}
		private:
			
			
			State m_state;
			Cpu::Registers m_reg;
			std::shared_ptr<MMU::MMU> m_mmu;
	};
	export Cpu;
}