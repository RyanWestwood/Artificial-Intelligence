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
		std::size_t pos = g_AssetDirectory.find("Artificial");
		while (g_AssetDirectory[pos] != 92) {
			pos++;
		}
		g_AssetDirectory.erase(begin(g_AssetDirectory) + pos, end(g_AssetDirectory));
		g_AssetDirectory += "\\assets\\";
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