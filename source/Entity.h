#pragma once
#include "engine/Texture.h"
#include <ai/math/Vector2.h>
#include <SDL2/SDL.h>

struct Collider
{
  SDL_Rect Dimensions  = {0, 0, 0, 0};
  Vector2  PixelOffset = {0.f, 0.f};
};

struct Transform
{
  Vector2 Position      = {0.f, 0.f};
  Vector2 Velocity      = {0.f, 0.f};
  float   Rotation      = 0.f;
  float   RotationSpeed = 0.f;
  char    Direction     = 0;
};

struct Image
{
  Sprite           Texture;
  char             AnimStep   = 0;
  char             NoOfAnims  = 0;
  SDL_RendererFlip FlipSprite = SDL_FLIP_NONE;
};

class Entity
{
public:
  Entity();

  virtual void Initialize();
  virtual void Input();
  virtual void Update(const float delta_time);
  virtual void UpdateAnimation();
  virtual void Draw();

  SDL_Rect& GetCollider();
  Vector2   GetNodePosition();

public:
  Collider  m_Collider;
  Transform m_Transform;
  Image     m_Image;
#if LOGGING
  texture::TextureData m_DebugCollider;
  bool                 m_DebugActivate = false;
#endif // LOGGING
};