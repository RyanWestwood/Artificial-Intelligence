#include "Player.h"
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

void Player::Update(double delta_time)
{
	m_Position.x += static_cast<float>(m_Velocity.x) * delta_time;
	m_Position.y += static_cast<float>(m_Velocity.y) * delta_time;

	m_Sprite.m_Destination.x = m_Position.x;
	m_Sprite.m_Destination.y = m_Position.y;
}

void Player::Draw()
{
	m_Sprite.Draw(m_FlipSprite);
}
