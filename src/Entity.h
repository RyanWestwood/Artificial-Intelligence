#pragma once
#include <SDL.h>
#include <math/Vector2.h>
#include "engine/Texture.h"

class Entity {
public:
	Entity();

	virtual void Initialize();
	virtual void Input();
	virtual void Update(const float delta_time) {}
	virtual void UpdateAnimation();
	virtual void Draw();

	SDL_Rect& GetCollider();
	SDL_Point GetNodePosition();

	// TODO @RyanWestwood: encapsulate fields in structs to make initialization easier! Same with Enemy.h
public:
	Sprite m_Sprite;
	SDL_Rect m_Collider;
	SDL_Point m_ColliderOffset;
#if LOGGING
	Texture::TextureData m_DebugCollider;
	bool m_DebugActivate = false;
#endif // LOGGING
	Vector2 m_Position;
	float m_Rotation;
	SDL_Point m_Velocity;
	char m_Direction;
	char m_AnimStep;
	char m_NoOfAnims;
	SDL_RendererFlip m_FlipSprite;
};