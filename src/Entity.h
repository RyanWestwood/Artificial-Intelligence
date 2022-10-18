#pragma once
#include <SDL.h>
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

public:
	Sprite m_Sprite;
	SDL_Rect m_Collider;
	SDL_Point m_ColliderOffset;
#if LOGGING
	Texture::TextureData m_DebugCollider;
	bool m_DebugActivate = false;
#endif // LOGGING
	SDL_FPoint m_Position;
	SDL_Point m_Velocity;
	char m_Direction;
	char m_AnimStep;
	char m_NoOfAnims;
	SDL_RendererFlip m_FlipSprite;
};