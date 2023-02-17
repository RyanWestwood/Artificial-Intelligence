#pragma once
#include <string>

namespace globals
{

  enum class Direction
  {
    North = 0,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest,
    None
  };

  bool        InitializeGlobals();
  std::string GetAssetDirectory();

  struct Vector
  {
    int w, h;
  };
  Vector GetScreenDimensions();
  Vector GetTileDimensions();
  Vector GetTileMapDimensions();

} // namespace globals