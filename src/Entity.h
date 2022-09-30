#pragma once
#include <SDL.h>
#include "engine/Texture.h"

class Entity {
public:
	Entity();

	virtual void Input() {};
	virtual void Update(double delta_time) {};
	virtual void UpdateAnimation() {};
	virtual void Draw() {};

public:
	Sprite m_Sprite;
	SDL_FRect m_Collider;
	SDL_FPoint m_Position;
	SDL_Point m_Velocity;
	char m_Direction;
	char m_AnimStep;
	SDL_RendererFlip m_FlipSprite;
};