#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace Renderer {

	extern SDL_Window* g_Window;
	extern SDL_Renderer* g_Renderer;

	constexpr int SCREEN_WIDTH = 1536;
	constexpr int SCREEN_HEIGHT = 864;

	bool InitalizeSDL();
	void UninitalizeSDL();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
}