#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace Renderer {

	bool InitalizeSDL();
	void UninitalizeSDL();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
}