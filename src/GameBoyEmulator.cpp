// GameBoyEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <memory>
#include <experimental/coroutine>
#include <experimental/generator>
 #define SDL_MAIN_HANDLED
#include <SDL.h>


//import std.core;
import Cpu;
import Registers;
import MMU;
import Cartridge;
import Gpu;

int main(int argc, char* argv[])
{
      //  std::cout.setstate(std::ios_base::failbit);
          SDL_SetMainReady();

   if(SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
      return 1;
   }

   SDL_Window* window;
   SDL_Renderer* renderer;
   SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &window, &renderer);
   if (window == nullptr || renderer == nullptr) {
      std::cout << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError() << "\n";
      SDL_Quit();
      return 1;
   }

   SDL_RenderSetLogicalSize(renderer, 160, 144);

   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 144; i++) {
      for (int j = 0; j < 160; j++) {
         SDL_RenderDrawPoint(renderer, j,i);
      }
    }
    SDL_RenderPresent(renderer);
   
   std::string cartFile("Tetris.gb");
   std::string bootrom("boot.gb");
   auto spMMU = std::make_shared<MMU::MMU>(bootrom);
   spMMU->loadCartridge(cartFile);
   Cpu::Cpu cpu(spMMU);
   Gpu::Gpu gpu(spMMU, renderer);
   while(true) {
      gpu.step();
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
