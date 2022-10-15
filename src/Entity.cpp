#include "Entity.h"

Entity::Entity() {
	m_Sprite = Sprite();
	m_Collider = { 0,0,0,0 };
	m_Position = { 0,0 };
	m_Direction = 0;
	m_Velocity = { 0, 0 };
	m_FlipSprite = SDL_FLIP_NONE;
	m_AnimStep = 0;
}

void Entity::UpdateAnimation()
{
	m_AnimStep >= m_NoOfAnims ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source.x = m_Sprite.m_Source.w * m_AnimStep;
}