
export module Cpu;

import Registers;

namespace Cpu
{
	class Cpu
	{
		public:
			Cpu() = default;
			~Cpu() = default;
		private:
			Cpu::Registers reg;
	};
	export Cpu;
}