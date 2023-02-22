#define SDL_MAIN_HANDLED
#include <engine/Globals.h>
#include <engine/Renderer.h>
#include <engine/Texture.h>

int main()
{
  bool globals  = globals::InitializeGlobals();
  bool renderer = renderer::InitializeRenderer();
  bool texture  = texture::InitializeTexture();
  if(!globals || !renderer || !texture) return 1;

  Sprite sprite;
  sprite.Initialize("tilemap.png");
  sprite.m_Source      = {336, 16, 16, 32};
  sprite.m_Destination = {128, 128, 24, 48};

  SDL_RenderClear(renderer::GetRenderer());
  sprite.Draw();
  SDL_RenderPresent(renderer::GetRenderer());
  return 0;
}