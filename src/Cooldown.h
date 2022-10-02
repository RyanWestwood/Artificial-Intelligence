#pragma once
#include "engine/Texture.h"
#include "engine/Font.h"

class Cooldown {
public:
	Cooldown() {}

	void Initialize(SDL_Point position);
	void Update(float delta_time);
	void Draw();

public:
	Sprite m_Background;
	Sprite m_Foreground;
	Text m_Text;
	float m_Distance;
	float m_Timer;
	float m_Cooldown;
};