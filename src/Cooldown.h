#pragma once
#include <iostream>
#include <string>
#include "engine/Font.h"
#include "engine/Texture.h"

class Cooldown {
public:
	Cooldown() {}

	void Start();

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
	std::string m_Message;
	bool m_IsCountingDown;
};