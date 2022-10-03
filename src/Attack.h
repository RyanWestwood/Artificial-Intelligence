#pragma once
#include <SDL.h>
#include "engine/Texture.h"

class Attack{
public:
	Attack(){}

public:
	Sprite m_Sprite;

protected:
	float m_Timer;
	float m_Cooldown;
	float m_Rotation;
	SDL_Point m_Center;
	bool m_Swing;
	SDL_RendererFlip m_Flip;
};