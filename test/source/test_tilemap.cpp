#define SDL_MAIN_HANDLED
#include <engine/Globals.h>
#include <engine/Renderer.h>
#include <engine/Texture.h>
#include <iostream>
#include <Tilemap.h>

int main()
{
  bool globals  = globals::InitializeGlobals();
  bool renderer = renderer::InitializeRenderer();
  bool texture  = texture::InitializeTexture();
  if(!globals || !renderer || !texture) return 1;

  Tilemap tilemap;
  tilemap.Initialize("tilemap.png", 16);

  std::cout << tilemap.m_Tiles.size() << "\n";

  SDL_RenderClear(renderer::GetRenderer());
  tilemap.Draw();
  SDL_RenderPresent(renderer::GetRenderer());

  return 0;
}