#include "Globals.h"
#include <SDL.h>
#include <iostream>

namespace Globals {

	namespace {
		extern std::string g_AssetDirectory = "Not yet initialized!\n";
	}

	bool Initialize() 
	{
		g_AssetDirectory = SDL_GetBasePath();
		for (char i = 0; i < 2; i++) {
			char currentChar = 'a';
			while (currentChar != '\\') {
				g_AssetDirectory.pop_back();
				currentChar = g_AssetDirectory.back();
			}
		}
		g_AssetDirectory += "assets/";
#ifdef LOGGING
		std::cout << "Globals Initialized!\n";
#endif
		return true;
	}

	std::string GetAssetDirectory()
	{
		return g_AssetDirectory;
	}
} // namespace Globals