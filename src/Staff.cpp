#include "Staff.h"

Staff::Staff()
{
	m_Cooldown = 1.f;
	m_Timer = 2.5f;
	m_Rotation = 0;
	m_Center = { 12,40 };
	m_Swing = false;
	m_Flip = SDL_FLIP_NONE;
}

void Staff::Initialize(const char* filename, float timer)
{
#ifdef LOGGING
	std::cout << "Staff initialize\n";
#endif // LOGGING
	m_Sprite.Initialize("tilemap.png");
	m_Sprite.m_Source = { 336, 144,16,32 };
	m_Sprite.m_Destination = { 128,128,16,32 };
	m_Timer = timer;
	m_Cooldown = timer;
}

void Staff::Update(const float& delta_time, const SDL_FPoint position)
{

}

void Staff::Draw(const SDL_RendererFlip& flip /*= SDL_FLIP_NONE*/)
{
	m_Sprite.Draw();
}

void Staff::Fire()
{
}