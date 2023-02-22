#pragma once
#include "../Entity.h"
#include "Globals.h"
#include "Texture.h"
#include <ai/pf/Algorithms.h>
#include <SDL2/SDL.h>

namespace pathing
{
  class Node : public Entity
  {
  public:
    Node() :
      Entity::Entity()
    {
      m_Position    = {0.f, 0.f};
      m_Destination = {0, 0, 0, 0};

#ifdef LOGGING
      m_TextureData = {
        nullptr, SDL_Rect{0, 0, 0, 0}
      };
#endif // LOGGING
    }

  public:
    SDL_FPoint m_Position;
    SDL_FRect  m_Destination;
#ifdef LOGGING
    void                 Draw();
    texture::TextureData m_TextureData;
#endif // LOGGING
  };

  enum class Algo
  {
    A_Star = 0,
    BFS,
    DFS,
    GBFS,
    DLS,
    IDDFS
  };

  bool InitializePathing();
  void UnInitialize();

  std::vector<Vector2> CreatePath(Vector2            start_node,
                                  Vector2            end_node,
                                  Algo               algorithm = Algo::A_Star,
                                  ai::path::Obstacle layer     = ai::path::Obstacle::None);
  void                 Reset();
  void                 SetObstacle(int x, int y, ai::path::Obstacle value);
  void                 UpdateAi();
  std::vector<Node>&   GetMap();

#ifdef LOGGING
  void DebugPaths(Vector2 tilemap_dimensions,
                  Vector2 tile_size);
  void Input();
  void Draw();
#endif // LOGGING
} // namespace pathing