#include "Player.h"
#include <algorithm>
#include "engine/Input.h"

constexpr int SPEED = 128;

Player::Player() : Entity()
{

}

void Player::Initialize()
{
	m_Sprite.Initialize("player.png");
	m_Sprite.m_Source = { 0,0,16,32 };
	m_Sprite.m_Destination = { 128,128,32,64 };

	m_Sword.Initialize("tilemap.png");
}

void Player::Input()
{
	if (Input::GetKeyDown(SDL_SCANCODE_LEFT)) {
		m_Velocity.x = -SPEED;
		m_FlipSprite = SDL_FLIP_HORIZONTAL;
	}
	if (Input::GetKeyDown(SDL_SCANCODE_RIGHT)) {
		m_Velocity.x = SPEED;
		m_FlipSprite = SDL_FLIP_NONE;
	}
	if (Input::GetKeyDown(SDL_SCANCODE_UP)) {
		m_Velocity.y = -SPEED;
	}	
	if (Input::GetKeyDown(SDL_SCANCODE_DOWN)) {
		m_Velocity.y = SPEED;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_SPACE)) {
		m_Sword.Swing();
	}

	if (Input::GetKeyUp(SDL_SCANCODE_LEFT)) {
#ifdef LOGGING
		std::cout << "Key Up: Left!\n";
#endif
		m_Velocity.x = 0;
		Input::SetKeyUp(SDL_SCANCODE_LEFT, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_RIGHT)) {
#ifdef LOGGING
		std::cout << "Key Up: Right!\n";
#endif
		m_Velocity.x = 0;
		Input::SetKeyUp(SDL_SCANCODE_RIGHT, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_UP)) {
#ifdef LOGGING
		std::cout << "Key Up: Up!\n";
#endif
		m_Velocity.y = 0;
		Input::SetKeyUp(SDL_SCANCODE_UP, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_DOWN)) {
#ifdef LOGGING
		std::cout << "Key Up: Down!\n";
#endif
		m_Velocity.y = 0;
		Input::SetKeyUp(SDL_SCANCODE_DOWN, false);
	}
}

void Player::Update(const float delta_time)
{
	
	m_Position.x = std::clamp(m_Position.x + static_cast<float>(m_Velocity.x) * delta_time, 0.f, 1536.f - 32.f);
	m_Position.y = std::clamp(m_Position.y + static_cast<float>(m_Velocity.y) * delta_time, -16.f, 864.f - 64.f);

	m_Sprite.m_Destination.x = m_Position.x;
	m_Sprite.m_Destination.y = m_Position.y;

	m_Sword.Update(delta_time, { m_Position.x + ((!m_FlipSprite << 5) - 14) , m_Position.y + 2 });
}

void Player::UpdateAnimation()
{
	m_AnimStep >= 7 ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source = { 16 * m_AnimStep, 0,16,32 };
}

void Player::Draw()
{
	m_Sprite.Draw(m_FlipSprite);
	m_Sword.Draw(m_FlipSprite);
}
