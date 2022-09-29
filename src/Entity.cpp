#include "Entity.h"

Entity::Entity() {
	m_Sprite = Sprite();
	m_Collider = { 0,0,0,0 };
	m_Position = { 0,0 };
	m_Direction = 0;
	m_Velocity = { 0, 0 };
	m_FlipSprite = SDL_FLIP_NONE;
}