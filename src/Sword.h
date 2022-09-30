#pragma once
#include "engine/Texture.h"

class Sword{
public:
	Sword();

	void Initialize(const char* filename);

	void Update(const float& delta_time, const SDL_FPoint position);
	void Draw(const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void Swing();

public:
	Sprite m_Sprite;

private:
	float m_Timer;
	float m_Cooldown;
	float m_Rotation;
	SDL_Point m_Center;
	bool m_Swing;
	SDL_RendererFlip m_Flip;
};