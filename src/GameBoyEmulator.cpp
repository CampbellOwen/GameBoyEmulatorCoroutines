// GameBoyEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <experimental/coroutine>
#include <experimental/generator>


//import std.core;
import Cpu;



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
    Cpu::Registers reg;
    std::cout << "Registers:\n";
    std::cout << reg.AF() << "\n";
    reg.AF(255);
    std::cout << std::hex << +reg.A << "\n";
    std::cout << std::hex << +reg.F << "\n";
    std::cout << std::hex << +reg.AF() << "\n";

    std::cout << "Flags\n";
    reg.F = 0;
    std::cout << std::hex << +reg.F << "\n";
    std::cout << std::hex << reg.Zero() << "\n";

    reg.Zero(true);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";


    reg.Sub(true);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

    reg.HalfCarry(true);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

    reg.Carry(true);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

    reg.Zero(false);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

    reg.Sub(false);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

    reg.HalfCarry(false);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

    reg.Carry(false);
    std::cout << std::hex << +reg.F << "\n";
    std::cout << "Zero " << std::hex << reg.Zero() << "\n";
    std::cout << "Sub " << std::hex << reg.Sub() << "\n";
    std::cout << "HalfCarry " << std::hex << reg.HalfCarry() << "\n";
    std::cout << "Carry " << std::hex << reg.Carry() << "\n";

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
