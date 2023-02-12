#define SDL_MAIN_HANDLED
#include <engine/Renderer.h>
#include <engine/Globals.h>
#include <engine/Texture.h>
#include <engine/Font.h>

int main() {
  
	bool globals = globals::InitializeGlobals();
	bool renderer = renderer::InitializeRenderer();
	bool texture = texture::InitializeTexture();
    bool font = font::InitializeFont();
    if(!globals || !renderer || !texture || !font) return 1;

    Text text;
    text.Initalize("Hello world!");

	return 0;
}