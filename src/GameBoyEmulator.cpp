// GameBoyEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <experimental/coroutine>
#include <experimental/generator>
#include <memory>


//import std.core;
import Cpu;
import Registers;
import MMU;
import Cartridge;

std::experimental::generator<int> iota(int n) {
   for (int i = 1; i < n+1; i++) {
      co_yield i;
   }

}

int main(int argc, char* argv[])
{
      //  std::cout.setstate(std::ios_base::failbit);

   std::cout << "Hello World!\n";
   auto gen = iota(10);
   
   for (auto i : gen) {
      std::cout << i << "\n";
   }

   std::string cartFile("Tetris.gb");
   std::string bootrom("boot.gb");
   auto spMMU = std::make_shared<MMU::MMU>(bootrom);
   spMMU->loadCartridge(cartFile);
   Cpu::Cpu cpu(spMMU);
   while(true) {
      cpu.step();
      // cpu.dumpRegisters();
   }
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
