#pragma once
#include "engine/Texture.h"

class Sword{
public:
	Sword();

	void Initialize(const char* filename);

	void Update(float delta_time, const SDL_FPoint position);
	void Draw();
	void Swing();

public:
	Sprite m_Sprite;

private:
	float m_Timer;
	float m_Cooldown;
};