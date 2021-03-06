#include "CppUnitTest.h"

#include <stdio.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

import Registers;
import MMU;
import Cartridge;
import Instructions;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameBoyEmulatorTests
{
	TEST_CLASS(RegistersTests)
	{
	public:
		
		TEST_METHOD(ZeroInitialized)
		{
			Cpu::Registers reg;
			Assert::AreEqual(0, (int)reg.A);
			Assert::AreEqual(0, (int)reg.F);
			Assert::AreEqual(0, (int)reg.B);
			Assert::AreEqual(0, (int)reg.C);
			Assert::AreEqual(0, (int)reg.D);
			Assert::AreEqual(0, (int)reg.E);
			Assert::AreEqual(0, (int)reg.H);
			Assert::AreEqual(0, (int)reg.L);
			Assert::AreEqual(0, (int)reg.SP);
			Assert::AreEqual(0, (int)reg.PC);
		}

		TEST_METHOD(RegisterAF)
		{
			Cpu::Registers reg;
			reg.AF(0x1234);
			Assert::AreEqual(0x12, (int)reg.A);
			Assert::AreEqual(0x34, (int)reg.F);
			Assert::AreEqual(0x1234, (int)reg.AF());
		}
		TEST_METHOD(RegisterBC)
		{
			Cpu::Registers reg;
			reg.BC(0x1234);
			Assert::AreEqual(0x12, (int)reg.B);
			Assert::AreEqual(0x34, (int)reg.C);
			Assert::AreEqual(0x1234, (int)reg.BC());
		}
		TEST_METHOD(RegisterDE)
		{
			Cpu::Registers reg;
			reg.DE(0x1234);
			Assert::AreEqual(0x12, (int)reg.D);
			Assert::AreEqual(0x34, (int)reg.E);
			Assert::AreEqual(0x1234, (int)reg.DE());
		}
		TEST_METHOD(RegisterHL)
		{
			Cpu::Registers reg;
			reg.HL(0x1234);
			Assert::AreEqual(0x12, (int)reg.H);
			Assert::AreEqual(0x34, (int)reg.L);
			Assert::AreEqual(0x1234, (int)reg.HL());
		}

		TEST_METHOD(RegisterFlags)
		{
			Cpu::Registers reg;

			reg.Zero(true);
			Assert::AreEqual(0b10000000, (int)reg.F);

			reg.Sub(true);
			Assert::AreEqual(0b11000000, (int)reg.F);

			reg.HalfCarry(true);
			Assert::AreEqual(0b11100000, (int)reg.F);

			reg.Carry(true);
			Assert::AreEqual(0b11110000, (int)reg.F);
			
			reg.Zero(false);
			Assert::AreEqual(0b01110000, (int)reg.F);

			reg.Sub(false);
			Assert::AreEqual(0b00110000, (int)reg.F);

			reg.HalfCarry(false);
			Assert::AreEqual(0b00010000, (int)reg.F);

			reg.Carry(false);
			Assert::AreEqual(0b00000000, (int)reg.F);
		}
	};

	TEST_CLASS(MMUTests)
	{
	public:
		TEST_METHOD(MMUinit)
		{
			MMU::MMU mmu("..\\boot.gb");
		
		}

		TEST_METHOD(DisableBootrom)
		{
			MMU::MMU mmu("..\\boot.gb");
			Assert::IsTrue(mmu.m_readFromBootrom);
			mmu.setByte(0xFF50, 1);
			Assert::IsFalse(mmu.m_readFromBootrom);
		}

		TEST_METHOD(Bootrom)
		{

			std::string filename("..\\boot.gb");
			MMU::MMU mmu(filename);
			std::ifstream infile(filename, std::ios::binary | std::ios::in);
			char temp {0};
			uint8_t currByte {0};
			size_t i {0};

			wchar_t message[256];

			for(int i = 0; i < 0x100; i++)
			{
				infile.get(temp);
				currByte = static_cast<uint8_t>(temp);

				auto cartByte = mmu.readByte(i);

				swprintf(message, L"At byte [%x]", i);

				Assert::AreEqual(currByte, *cartByte, message);
			}
		}
	};

	TEST_CLASS(CartridgeTests)
	{
	public:
		TEST_METHOD(LoadCartridge)
		{
			
			std::string filename("..\\Tetris.gb");

			std::ifstream infile(filename, std::ios::binary | std::ios::in);
			char temp {0};
			uint8_t currByte {0};
			size_t i {0};
	

			Cartridge::Cartridge cart(filename);

			std::cout << "Is stream open? " << infile.is_open() << "\n";
			// Assert::IsTrue(infile.is_open());
			while (infile)
			{
				infile.get(temp);
				currByte = static_cast<uint8_t>(temp);

				auto cartByte = cart.readByte(i);
				Assert::AreEqual(currByte, *cartByte);

				i++;
			}
		}
	};

	TEST_CLASS(InstructionsTests)
	{
		TEST_METHOD(OpcodesCorrect)
		{
			for(uint8_t i = 0; i < 0x100; i++) {
				Assert::AreEqual(i, Cpu::instructions[i].opcode);
			}	
		}

		TEST_METHOD(AllImplemented)
		{
			for(auto inst : Cpu::instructions)
			{
				Assert::IsTrue(strcmp("UNIMPLEMENTED", inst.name));
			}
		}
	};
}
