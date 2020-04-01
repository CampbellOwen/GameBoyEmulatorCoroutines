// GameBoyEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <experimental/coroutine>
#include <experimental/generator>


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
   std::cout << "Hello World!\n";
   auto gen = iota(10);
   
   for (auto i : gen) {
      std::cout << i << "\n";
   }

   std::string filename("Tetris.gb");

   std::ifstream infile(filename, std::ios::binary | std::ios::in);
   char temp {0};
   uint8_t currByte {0};
   size_t i {0};

   std::cout << "Is stream open? " << infile.is_open() << "\n";
   while (infile)
   {
      infile.get(temp);
      currByte = static_cast<uint8_t>(temp);

      std::cout << std::hex << +currByte << " ";
      if (i % 0xF == 0 && i) {
         std::cout << "\n";
      }

      i++;
   }

   std::cout << "Checking Cartridge\n";
   Cartridge::Cartridge cart(filename);

   std::cout << std::hex << +(*(cart.readByte(0))) << "\n";
   
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
