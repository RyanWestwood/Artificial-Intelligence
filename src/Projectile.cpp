#include "Projectile.h"

Projectile::Projectile()
{
	m_Active = false;
}

void Projectile::Initialize()
{
	m_Sprite.Initialize("projectile.png");
	m_Sprite.m_Source = { 0,0,32,32 };
	m_Sprite.m_Destination = { 128,128,32,32 };
}

void Projectile::Activate() {
	m_Active = true;
}

void Projectile::Update(const float delta_time)
{
	if (!m_Active) return;
	m_Position.x += 32.f * delta_time;
	m_Sprite.m_Destination.x = m_Position.x;
	std::cout << "update!\n";
}

void Projectile::UpdateAnimation()
{
	if (!m_Active) return;
	m_AnimStep >= 7 ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source.x = 32 * m_AnimStep;
}

void Projectile::Draw()
{
	if (!m_Active) return;
	m_Sprite.Draw();
	std::cout << m_Sprite.m_Destination.x << ", Y:\y" << m_Sprite.m_Destination.y << "\n";
	std::cout << m_Sprite.m_Destination.w << ", H:\t" << m_Sprite.m_Destination.h << "\n";
}
