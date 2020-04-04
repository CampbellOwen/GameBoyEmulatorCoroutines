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
   
   std::string cartFile("Tetris.gb");
   std::string bootrom("boot.gb");
   auto spMMU = std::make_shared<MMU::MMU>(bootrom);
   spMMU->loadCartridge(cartFile);
   Cpu::Cpu cpu(spMMU);
   Gpu::Gpu gpu(spMMU, renderer);
   while(true) {
      gpu.step();
      cpu.step();
   }
   
}