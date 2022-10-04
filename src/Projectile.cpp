#include "Projectile.h"

Projectile::Projectile()
{

}

void Projectile::Initialize()
{
	m_Sprite.Initialize("projectile.png");
	m_Sprite.m_Source = { 0,0,32,32 };
	m_Sprite.m_Destination = { 128,128,32,32 };
}

void Projectile::Update(const float delta_time)
{
	m_Position.x += 32.f * delta_time;
	m_Sprite.m_Destination.x = m_Position.x;
}

void Projectile::UpdateAnimation()
{
	m_AnimStep >= 7 ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source.x = 32 * m_AnimStep;
}

void Projectile::Draw()
{
	m_Sprite.Draw();
}
