#include "Entity.h"
#include "engine/Renderer.h"
#include "engine/Input.h"

Entity::Entity() {
	m_Sprite = Sprite();
	m_Collider = { 0,0,0,0 };
	m_Position = { 0,0 };
	m_Direction = 0;
	m_Velocity = { 0, 0 };
	m_FlipSprite = SDL_FLIP_NONE;
	m_AnimStep = 0;
}

void Entity::Initialize()
{
#if LOGGING
	m_DebugCollider = Texture::LoadDebugTexture({ 0,255,255,128 }, { 32,32 });
#endif // LOGGING
}

void Entity::Input()
{
#if LOGGING
	if (Input::GetKeyUp(SDL_SCANCODE_F3)) {
		m_DebugActivate = !m_DebugActivate;
	}
#endif // LOGGING
}

void Entity::UpdateAnimation()
{
	m_AnimStep >= m_NoOfAnims ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source.x = m_Sprite.m_Source.w * m_AnimStep;
}

void Entity::Draw()
{
#if LOGGING
	if (m_DebugActivate){
		SDL_RenderCopy(Renderer::GetRenderer(), m_DebugCollider.m_Texture, &m_DebugCollider.m_Source, &m_Collider);
	}
#endif // LOGGING
}

SDL_Rect& Entity::GetCollider()
{
	return m_Collider;
}

SDL_Point Entity::GetNodePosition()
{
	return { (int)m_Position.x / 32, (int)m_Position.y / 32 };
}