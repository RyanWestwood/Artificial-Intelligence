#define SDL_MAIN_HANDLED
#include <engine/Globals.h>
#include <engine/Renderer.h>
#include <engine/Texture.h>
#include <Tilemap.h>

#include <iostream>

int main() {
  
	bool globals = globals::Initialize();
	bool renderer = renderer::InitializeRenderer();
	bool texture = texture::Initialize();

	Tilemap tilemap;
	tilemap.Initialize("tilemap.png", 16);

	std::cout << tilemap.m_Tiles.size() << "\n";

	SDL_RenderClear(renderer::GetRenderer());
	tilemap.Draw();
	SDL_RenderPresent(renderer::GetRenderer());

	return 0;
}