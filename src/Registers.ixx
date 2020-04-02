#include <cstdint>
#include <memory>

#define Z_POS 7
#define N_POS 6
#define H_POS 5
#define C_POS 4


export module Registers;
import MMU;

namespace Cpu 
{
struct Registers {
	
		uint8_t A{ 0 };
		uint8_t B{ 0 };
		uint8_t C{ 0 };
		uint8_t D{ 0 };
		uint8_t E{ 0 };
		uint8_t F{ 0 };
		uint8_t H{ 0 };
		uint8_t L{ 0 };
		uint16_t SP{ 0 };
		uint16_t PC{ 0 };

		uint16_t AF() {
			return get16(A, F);
		}
		void AF(uint16_t val) {
			set16(A, F, val);
		
		}
		uint16_t BC() {
			return get16(B, C);
		}
		void BC(uint16_t val) {
			set16(B, C, val);
		}
		uint16_t DE() {
			return get16(D, E);
		}
		void DE(uint16_t val) {
			set16(D, E, val);
		}
		uint16_t HL() {
			return get16(H, L);
		}
		void HL(uint16_t val) {
			set16(H, L, val);
		}

		bool Zero() {
			return getBit(F, Z_POS);
		}
		void Zero(bool bit) {
			setBit(F, Z_POS, bit);
		}

		bool Sub() {
			return getBit(F, N_POS);
		}
		void Sub(bool bit) {
			setBit(F, N_POS, bit);
		}

		bool HalfCarry() {
			return getBit(F, H_POS);
		}
		void HalfCarry(bool bit) {
			setBit(F, H_POS, bit);
		}

		bool Carry() {
			return getBit(F, C_POS);
		}
		void Carry(bool bit) {
			setBit(F, C_POS, bit);
		}

		void setPC(uint8_t high, uint8_t low)
		{
			PC = (high << 8) | low;
		}

		void setSP(uint8_t high, uint8_t low)
		{
			SP = (high << 8) | low;
		}

		uint8_t reg(const std::shared_ptr<MMU::MMU>& mmu, uint8_t index)
		{
			auto valRead = mmu->readByte(HL());
			switch (index) {
				case 0:
					return B;
				case 1:
					return C;
				case 2:
					return D;
				case 3:
					return E;
				case 4:
					return H;
				case 5:
					return L;
				case 6:
					if (!valRead) {
						return 0;
					}
					return *valRead;
				case 7:
					return A;
			}

			return 0;
		}

		void reg(const std::shared_ptr<MMU::MMU>& mmu, uint8_t index, uint8_t value)
		{
			switch (index) {
				case 0:
					B = value;
				break;
				case 1:
					C = value;
					break;
				case 2:
					D = value;
					break;
				case 3:
					E = value;
					break;
				case 4:
					H = value;
					break;
				case 5:
					L = value;
					break;
				case 6:
					mmu->setByte(HL(), value);
					break;
				case 7:
					A = value;
					break;
			}
		}

	private:
		void set16(uint8_t& high, uint8_t& low, uint16_t val)
		{
			high = val >> 8;
			low = val & 0xFF;
		}
		uint16_t get16(uint8_t high, uint8_t low)
		{
			return (high << 8) | low;
		}
		void setBit(uint8_t& reg, uint8_t pos, uint8_t bit) {
			reg = (reg & (~(1 << pos))) | (bit << pos);
		}

		bool getBit(uint8_t reg, uint8_t pos)
		{
			return reg & (1 << pos);
		}
	};
    
export Registers;

}
