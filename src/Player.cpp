#include "Player.h"
#include <algorithm>
#include "engine/Input.h"
#include "engine/Globals.h"

constexpr int g_MoveSpeed = 128;

Player::Player() : Entity()
{

}

void Player::Initialize()
{
	m_Sprite.Initialize("player.png");
	m_Sprite.m_Source = { 0,0,16,32 };
	m_Sprite.m_Destination = { 128,128,32,64 };

	m_Sword.Initialize("tilemap.png", 2.f);
	m_MeleeCooldown.Initialize({ 16,784 }, 2.f);
	m_RangedCooldown.Initialize({ 96, 784 }, 2.f);
}

void Player::Input()
{
	if (Input::GetKeyDown(SDL_SCANCODE_LEFT)) {
		m_Velocity.x = -g_MoveSpeed;
		m_FlipSprite = SDL_FLIP_HORIZONTAL;
	}
	if (Input::GetKeyDown(SDL_SCANCODE_RIGHT)) {
		m_Velocity.x = g_MoveSpeed;
		m_FlipSprite = SDL_FLIP_NONE;
	}
	if (Input::GetKeyDown(SDL_SCANCODE_UP)) {
		m_Velocity.y = -g_MoveSpeed;
	}	
	if (Input::GetKeyDown(SDL_SCANCODE_DOWN)) {
		m_Velocity.y = g_MoveSpeed;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_SPACE)) {
		m_Sword.Swing();
		m_MeleeCooldown.Start();
		m_RangedCooldown.Start();
	}

	if (Input::GetKeyUp(SDL_SCANCODE_LEFT)) {
#ifdef LOGGING
		std::cout << "Key Up: Left!\n";
#endif // LOGGING
		m_Velocity.x = 0;
		Input::SetKeyUp(SDL_SCANCODE_LEFT, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_RIGHT)) {
#ifdef LOGGING
		std::cout << "Key Up: Right!\n";
#endif // LOGGING
		m_Velocity.x = 0;
		Input::SetKeyUp(SDL_SCANCODE_RIGHT, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_UP)) {
#ifdef LOGGING
		std::cout << "Key Up: Up!\n";
#endif // LOGGING
		m_Velocity.y = 0;
		Input::SetKeyUp(SDL_SCANCODE_UP, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_DOWN)) {
#ifdef LOGGING
		std::cout << "Key Up: Down!\n";
#endif // LOGGING
		m_Velocity.y = 0;
		Input::SetKeyUp(SDL_SCANCODE_DOWN, false);
	}
}

void Player::Update(const float delta_time)
{
	auto screen_dimensions = Globals::GetScreenDimensions();
	m_Position.x = std::clamp(m_Position.x + static_cast<float>(m_Velocity.x) * delta_time, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Position.y = std::clamp(m_Position.y + static_cast<float>(m_Velocity.y) * delta_time, -16.f, screen_dimensions.h - 64.f); // Offsetting image size

	m_Sprite.m_Destination.x = m_Position.x;
	m_Sprite.m_Destination.y = m_Position.y;

	SDL_FPoint sword_position = { m_Position.x + ((!m_FlipSprite << 5) - 14) , m_Position.y + 2 }; // Sets the sword left or right of the player
	m_Sword.Update(delta_time, sword_position);

	m_MeleeCooldown.Update(delta_time);
	m_RangedCooldown.Update(delta_time);
}

void Player::UpdateAnimation()
{
	m_AnimStep >= 7 ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source.x = 16 * m_AnimStep;
}

void Player::Draw()
{
	m_Sprite.Draw(m_FlipSprite);
	m_Sword.Draw(m_FlipSprite);
	m_MeleeCooldown.Draw();
	m_RangedCooldown.Draw();
}
