#define SDL_MAIN_HANDLED
#include <engine/Renderer.h>

int main()
{
  bool renderer = renderer::InitializeRenderer();
  if(!renderer) return 1;

  renderer::UninitalizeRenderer();

  return 0;
}