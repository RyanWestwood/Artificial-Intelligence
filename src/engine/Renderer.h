#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace Renderer {

	bool InitalizeRenderer();
	void UninitalizeRenderer();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
}