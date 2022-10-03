#include "Sword.h"
#include <iostream>
#include <algorithm>

constexpr float SWING_SPEED = 512.f;
constexpr float SWING_ROTATION = 90.f;

Sword::Sword()
{
	m_Cooldown = 1.f;
	m_Timer = 2.5f;
	m_Rotation = 0;
	m_Center = { 12,40 };
	m_Swing = false;
	m_Flip = SDL_FLIP_NONE;
}

void Sword::Initialize(const char* filename, float timer) {
#ifdef LOGGING
	std::cout << "Sword initialize\n";
#endif // LOGGING
	m_Sprite.Initialize("tilemap.png");
	m_Sprite.m_Source = { 336,16,16,32 };
	m_Sprite.m_Destination = { 128,128,24,48 };
	m_Timer = timer;
	m_Cooldown = timer;
}

void Sword::Update(const float& delta_time, const SDL_FPoint position)
{
	m_Timer += delta_time;

	m_Sprite.m_Destination.x = position.x;
	m_Sprite.m_Destination.y = position.y;

	if (m_Swing) {
		m_Rotation = std::clamp(m_Rotation + ((!m_Flip << 1) - 1) * delta_time * SWING_SPEED, -SWING_ROTATION, SWING_ROTATION);
		if (m_Rotation >= SWING_ROTATION || m_Rotation <= -SWING_ROTATION) {
			m_Swing = false;
			m_Rotation = 0.f;
		}
	}
}

void Sword::Draw(const SDL_RendererFlip& flip)
{
	m_Flip = flip;
	m_Sprite.Draw(m_Flip, m_Rotation, m_Center);
}

void Sword::Swing()
{
	if (m_Timer > m_Cooldown) {
		m_Rotation = 0.f;
		m_Swing = true;
		m_Timer = 0.f;
	}
}
