#pragma once
#include <ai/math/Vector2.h>
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

  Vector2 GetScreenDimensions();
  Vector2 GetTileDimensions();
  Vector2 GetTileMapDimensions();

} // namespace globals