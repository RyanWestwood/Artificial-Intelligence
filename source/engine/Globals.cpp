#include "Globals.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace globals
{

  namespace
  {
    extern std::string      g_AssetDirectory    = "Not yet initialized!\n";
    extern const Vector2 g_ScreenDimensions  = Vector2(1536, 864);
    extern const Vector2 g_TileDimensions    = Vector2(32, 32);
    extern const Vector2 g_TileMapDimensions = Vector2(48, 27);
  } // namespace

  bool InitializeGlobals()
  {
    g_AssetDirectory = SDL_GetBasePath();
    std::size_t pos  = g_AssetDirectory.find("Carlos-Dungeon-Crusade");
    while(g_AssetDirectory[pos] != 92)
    {
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

  Vector2 GetScreenDimensions()
  {
    return g_ScreenDimensions;
  }

  Vector2 GetTileDimensions()
  {
    return g_TileDimensions;
  }

  Vector2 GetTileMapDimensions()
  {
    return g_TileMapDimensions;
  }

} // namespace globals