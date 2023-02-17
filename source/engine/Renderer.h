#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace renderer
{
  bool InitializeRenderer();
  void UninitalizeRenderer();

  SDL_Renderer* GetRenderer();
  SDL_Window*   GetWindow();
} // namespace renderer