#include "Projectile.h"
#include <algorithm>
#include "engine/Globals.h"
#include "engine/Renderer.h"

Projectile::Projectile(Texture::TextureData spritesheet, ProjectileManager* manager)
{
	m_Active = false;
	m_Manager = manager;
	m_Spritesheet = spritesheet;
	m_Spritesheet.m_Source.w = 32;
	m_Spritesheet.m_Source.h = 32;
	m_Destination = { 0,0,32,32 };
	m_Image.m_NoOfAnims = 7;
}

void Projectile::Activate(SDL_FPoint position, std::shared_ptr<Globals::Direction> facing) {
	m_Active = true;
	m_Transform.m_Position = { position.x, position.y };
	m_Transform.m_Velocity = { 512, 0 };
	m_Destination = { m_Transform.m_Position.x, m_Transform.m_Position.y,32,32 };

	if (*facing == Globals::Direction::North) SetDirection(0,-512, 270);
	if (*facing == Globals::Direction::NorthEast) SetDirection(512,-512, 315);
	if (*facing == Globals::Direction::East) SetDirection(512, 0, 0);
	if (*facing == Globals::Direction::SouthEast) SetDirection(512, 512, 45);
	if (*facing == Globals::Direction::South) SetDirection(0, 512, 90);
	if (*facing == Globals::Direction::SouthWest) SetDirection(-512, 512, 135);
	if (*facing == Globals::Direction::West) SetDirection(-512, 0, 180);
	if (*facing == Globals::Direction::NorthWest) SetDirection(-512, -512, 225);
}

void Projectile::Deactivate()
{
	m_Active = false;
	m_Manager->Deactivate(*this);
}

void Projectile::SetDirection(int x, int y, int angle){
	m_Transform.m_Velocity = { (float)x, (float)y };
	m_Angle = angle;
}

void Projectile::Update(const float& delta_time)
{
	auto screen_size = Globals::GetScreenDimensions();
	if (!m_Active) return;
	if (m_Transform.m_Position.x < -14 || m_Transform.m_Position.x >= screen_size.w + 14) Deactivate();
	if (m_Transform.m_Position.y < -14 || m_Transform.m_Position.y >= screen_size.h + 14) Deactivate();

	m_Transform.m_Position.x += m_Transform.m_Velocity.x * delta_time;
	m_Transform.m_Position.y += m_Transform.m_Velocity.y * delta_time;
	m_Destination.x = m_Transform.m_Position.x;
	m_Destination.y = m_Transform.m_Position.y;
}

void Projectile::UpdateAnimation()
{
	if (!m_Active) return;
	Entity::UpdateAnimation();
}

void Projectile::Draw()
{
	if (!m_Active) return;
	SDL_RenderCopyExF(Renderer::GetRenderer(), m_Spritesheet.m_Texture, &m_Spritesheet.m_Source, &m_Destination, m_Angle, 0, SDL_FLIP_NONE);
}

void ProjectileManager::Initialize(int no_of_projectiles)
{
	auto texture = Texture::LoadTexture("projectile.png");
	m_TextureData.m_Texture = texture.m_Texture;
	m_TextureData.m_Source = texture.m_Source;
	m_InactiveProjectiles = { Uint64(no_of_projectiles), Projectile(m_TextureData, this) };
	m_ActiveProjectiles.reserve(no_of_projectiles);
}

void ProjectileManager::Update(const float& delta_time)
{
	for (Projectile& projectile : m_ActiveProjectiles) {
		projectile.Update(delta_time);
	}
}

void ProjectileManager::UpdateAnimation()
{
	for(Projectile& projectile : m_ActiveProjectiles){
		projectile.UpdateAnimation();
	}
}

void ProjectileManager::Draw()
{
	for (Projectile& projectile : m_ActiveProjectiles) {
		projectile.Draw();
	}
}

void ProjectileManager::Activate(const SDL_FPoint& position, std::shared_ptr<Globals::Direction> facing)
{
	m_InactiveProjectiles.front().Activate(position, facing);
	m_ActiveProjectiles.insert(m_ActiveProjectiles.end(), std::make_move_iterator(m_InactiveProjectiles.begin()),
		std::make_move_iterator(m_InactiveProjectiles.begin()+1));
	m_InactiveProjectiles.erase(begin(m_InactiveProjectiles), begin(m_InactiveProjectiles) + 1);
}

void ProjectileManager::Deactivate(Projectile& projectile)
{
	m_InactiveProjectiles.insert(m_InactiveProjectiles.end(), std::make_move_iterator(m_ActiveProjectiles.begin()),
		std::make_move_iterator(m_ActiveProjectiles.begin() + 1));
	m_ActiveProjectiles.erase(begin(m_ActiveProjectiles), begin(m_ActiveProjectiles) + 1);
}