#include "Player.h"
#include <algorithm>
#include "engine/Input.h"

constexpr int g_MoveSpeed = 128;

Player::Player() : Entity()
{

}

void Player::Initialize()
{
	Entity::Initialize();
	m_Image.Texture.Initialize("player.png");
	m_Image.Texture.m_Source = { 0,0,16,32 };
	m_Image.Texture.m_Destination = { 128,128,32,64 };
	m_Image.NoOfAnims = 7;
	m_Collider = { 0,0,28,42 };
	m_Collider.PixelOffset = { 2,16 };
	m_Transform.Position = { 512,128 };

	m_OffGlobal = std::make_shared<float>(2.5f);
	m_Facing = std::make_shared<Globals::Direction>(Globals::Direction::None);

	m_Sword.Initialize("tilemap.png", m_OffGlobal, m_Facing);

	m_MeleeCooldown.Initialize({ 16,784 }, 2);
	m_RangedCooldown.Initialize({ 76, 784 }, 2);
	m_MitigationCooldown.Initialize({ 136, 784 }, 15);
	m_HealthRegenCooldown.Initialize({ 196, 784 }, 30);
}

void Player::KeyUp(SDL_Scancode code, const char* message)
{
	if (Input::GetKeyUp(code)) {
#ifdef LOGGING
		std::cout << message;
#endif // LOGGING
		Input::SetKeyUp(code, false);
	}	
}

void Player::Input()
{
	Entity::Input();
	if (Input::GetKeyDown(SDL_SCANCODE_LEFT)) {
		m_Transform.Velocity.x = -g_MoveSpeed;
		m_Image.FlipSprite = SDL_FLIP_HORIZONTAL;
	}
	if (Input::GetKeyDown(SDL_SCANCODE_RIGHT)) {
		m_Transform.Velocity.x = g_MoveSpeed;
		m_Image.FlipSprite = SDL_FLIP_NONE;
	}
	if (Input::GetKeyDown(SDL_SCANCODE_UP)) {
		m_Transform.Velocity.y = -g_MoveSpeed;
	}	
	if (Input::GetKeyDown(SDL_SCANCODE_DOWN)) {
		m_Transform.Velocity.y = g_MoveSpeed;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_A)) {
		m_Sword.Swing();
		m_MeleeCooldown.Start();
		m_RangedCooldown.Start();
	}
	if (Input::GetKeyDown(SDL_SCANCODE_S)) {
		m_Sword.Fire();
		m_MeleeCooldown.Start();
		m_RangedCooldown.Start();
	}
	if (Input::GetKeyDown(SDL_SCANCODE_D)) {
		Mitigation();
		m_MitigationCooldown.Start();
	}
	if (Input::GetKeyDown(SDL_SCANCODE_W)) {
		HealthSpell();
		m_HealthRegenCooldown.Start();
	}

	if (Input::GetKeyUp(SDL_SCANCODE_LEFT)) {
#ifdef LOGGING
		std::cout << "Key Up: Left!\n";
#endif // LOGGING
		m_Transform.Velocity.x = 0;
		Input::SetKeyUp(SDL_SCANCODE_LEFT, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_RIGHT)) {
#ifdef LOGGING
		std::cout << "Key Up: Right!\n";
#endif // LOGGING
		m_Transform.Velocity.x = 0;
		Input::SetKeyUp(SDL_SCANCODE_RIGHT, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_UP)) {
#ifdef LOGGING
		std::cout << "Key Up: Up!\n";
#endif // LOGGING
		m_Transform.Velocity.y = 0;
		Input::SetKeyUp(SDL_SCANCODE_UP, false);
	}
	if (Input::GetKeyUp(SDL_SCANCODE_DOWN)) {
#ifdef LOGGING
		std::cout << "Key Up: Down!\n";
#endif // LOGGING
		m_Transform.Velocity.y = 0;
		Input::SetKeyUp(SDL_SCANCODE_DOWN, false);
	}
	KeyUp(SDL_SCANCODE_A, "Sword swing!\n");
	KeyUp(SDL_SCANCODE_S, "Ranged attack!\n");
	KeyUp(SDL_SCANCODE_D, "Mitigation!\n");
	KeyUp(SDL_SCANCODE_W, "Health potion!\n");
}

void Player::Update(const float delta_time)
{
	if (m_Transform.Velocity.y < 0) *m_Facing = Globals::Direction::North;
	if (m_Transform.Velocity.x > 0) *m_Facing = Globals::Direction::East;
	if (m_Transform.Velocity.y < 0 && m_Transform.Velocity.x > 0) *m_Facing = Globals::Direction::NorthEast;
	if (m_Transform.Velocity.y > 0) *m_Facing = Globals::Direction::South;
	if (m_Transform.Velocity.y > 0 && m_Transform.Velocity.x > 0) *m_Facing = Globals::Direction::SouthEast;
	if (m_Transform.Velocity.x < 0) *m_Facing = Globals::Direction::West;
	if (m_Transform.Velocity.y > 0 && m_Transform.Velocity.x < 0) *m_Facing = Globals::Direction::SouthWest;
	if (m_Transform.Velocity.y < 0 && m_Transform.Velocity.x < 0) *m_Facing = Globals::Direction::NorthWest;
	if (m_Transform.Velocity.x == 0 && m_Transform.Velocity.y == 0) *m_Facing = Globals::Direction::None;

	auto screen_dimensions = Globals::GetScreenDimensions();
	m_Transform.Position.x = std::clamp(m_Transform.Position.x + static_cast<float>(m_Transform.Velocity.x) * delta_time, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Transform.Position.y = std::clamp(m_Transform.Position.y + static_cast<float>(m_Transform.Velocity.y) * delta_time, -16.f, screen_dimensions.h - 64.f); // Offsetting image size
	m_Collider.Dimensions.x = m_Transform.Position.x + m_Collider.PixelOffset.x;
	m_Collider.Dimensions.y = m_Transform.Position.y + m_Collider.PixelOffset.y;
	m_Image.Texture.m_Destination.x = m_Transform.Position.x;
	m_Image.Texture.m_Destination.y = m_Transform.Position.y;

	SDL_FPoint sword_position = { m_Transform.Position.x + ((!m_Image.FlipSprite << 5) - 14) , m_Transform.Position.y + 2 }; // Sets the sword left or right of the player
	m_Sword.Update(delta_time, sword_position);

	*m_OffGlobal += delta_time;
	m_MeleeCooldown.Update(delta_time);
	m_RangedCooldown.Update(delta_time);
	m_HealthRegenCooldown.Update(delta_time);
	m_MitigationCooldown.Update(delta_time);
}

void Player::Resume()
{
	Input::SetKeyDown(SDL_SCANCODE_LEFT, false);
	Input::SetKeyDown(SDL_SCANCODE_RIGHT, false);
	Input::SetKeyDown(SDL_SCANCODE_UP, false);
	Input::SetKeyDown(SDL_SCANCODE_DOWN, false);
	Input::SetKeyDown(SDL_SCANCODE_A, false);
	Input::SetKeyDown(SDL_SCANCODE_S, false);
	Input::SetKeyDown(SDL_SCANCODE_W, false);
	Input::SetKeyDown(SDL_SCANCODE_D, false);
	m_Transform.Velocity = {0,0};
}

void Player::UpdateAnimation()
{
	Entity::UpdateAnimation();
	m_Sword.UpdateAnimation();
}

void Player::Draw()
{
	Entity::Draw();
	m_Image.Texture.Draw(m_Image.FlipSprite);
	m_Sword.Draw(m_Image.FlipSprite);
	m_MeleeCooldown.Draw();
	m_RangedCooldown.Draw();
	m_HealthRegenCooldown.Draw();
	m_MitigationCooldown.Draw();
}
