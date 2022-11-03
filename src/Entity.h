#pragma once
#include <SDL.h>
#include <math/Vector2.h>
#include "engine/Texture.h"

struct Collider {
	SDL_Rect m_Dimensions;
	Vector2 m_PixelOffset;
};

struct Transform {
	Vector2 m_Position;
	float m_Rotation;
	SDL_Point m_Velocity;
	char m_Direction;
};

struct Image {

};

class Entity {
public:
	Entity();

	virtual void Initialize();
	virtual void Input();
	virtual void Update(const float delta_time) {}
	virtual void UpdateAnimation();
	virtual void Draw();

	SDL_Rect& GetCollider();
	Vector2 GetNodePosition();

public:
	Collider m_Collider;
	Transform m_Transform;
#if LOGGING
	Texture::TextureData m_DebugCollider;
	bool m_DebugActivate = false;
#endif // LOGGING
	Sprite m_Sprite;
	char m_AnimStep;
	char m_NoOfAnims;
	SDL_RendererFlip m_FlipSprite;
};