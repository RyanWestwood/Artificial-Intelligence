#include "Sword.h"
#include <iostream>

Sword::Sword()
{
	m_Cooldown = 2.5f;
	m_Timer = 2.5f;
}

void Sword::Initialize(const char* filename) {
#ifdef LOGGING
	std::cout << "Sword initialize\n";
#endif
	m_Sprite.Initialize("tilemap.png");
	m_Sprite.m_Source = { 336,16,16,32 };
	m_Sprite.m_Destination = { 128,128,24,48 };
}

void Sword::Update(float delta_time, const SDL_FPoint position)
{
	m_Timer += delta_time;

	m_Sprite.m_Destination.x = position.x;
	m_Sprite.m_Destination.y = position.y;
}

void Sword::Draw()
{
	m_Sprite.Draw();
}

void Sword::Swing()
{
	if (m_Timer > m_Cooldown) {
		std::cout << "boom!\n";
		m_Timer = 0;
	}
}
