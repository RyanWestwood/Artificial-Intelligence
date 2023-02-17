#pragma once
#include <SDL2/SDL.h>

struct Circle
{
  SDL_Point m_Position;
  int       m_Radius;
};

namespace collision
{
  bool BoxCollision(SDL_Rect& lhs, SDL_Rect& rhs);
  bool SphereCollision(Circle& lhs, Circle& rhs);
  bool ComplexCollision(Circle& lhs, SDL_Rect& rhs);
} // namespace collision