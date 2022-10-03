#include "Globals.h"
#include <SDL.h>
#include <iostream>

namespace Globals {

	namespace {
		extern std::string g_AssetDirectory = "Not yet initialized!\n";
		extern constexpr Vector g_ScreenDimensions = { 1536.f, 864.f };
		extern constexpr Vector g_TileDimensions = { 64.f, 64.f };
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
#endif // LOGGING
		return true;
	}

	std::string GetAssetDirectory()
	{
		return g_AssetDirectory;
	}

	Vector GetScreenDimensions()
	{
		return g_ScreenDimensions;
	}

	Globals::Vector GetTileDimensions()
	{
		return g_TileDimensions;
	}

} // namespace Globals