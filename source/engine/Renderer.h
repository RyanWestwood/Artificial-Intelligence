#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace renderer {

	bool InitializeRenderer();
	void UninitalizeRenderer();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
} // namespace Renderer