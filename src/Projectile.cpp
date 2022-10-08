#include "Projectile.h"
#include <algorithm>
#include "engine/Globals.h"
#include "engine/Renderer.h"

Projectile::Projectile(Texture::TextureData spritesheet)
{
	m_Active = false;
	m_Spritesheet = spritesheet;
	m_Spritesheet.m_Source.w = 32;
	m_Spritesheet.m_Source.h = 32;
	m_Destination = { 0,0,32,32 };
}

void Projectile::Activate(SDL_FPoint position) {
	m_Active = true;
	m_Position = { position.x, position.y };
	m_Destination = { 0,0,32,32 };
	m_Destination.x = m_Position.x;
	m_Destination.y = m_Position.y;
}

void Projectile::Deactivate()
{
	m_Active = false;
}

void Projectile::Update(const float& delta_time)
{
	auto screen_size = Globals::GetScreenDimensions();
	if (m_Position.x <= 0 || m_Position.x >= screen_size.w) Deactivate();
	if (m_Position.y <= -10 || m_Position.y >= screen_size.h) Deactivate();
	if (!m_Active) return;

	m_Position.x += 512.f * delta_time;
	m_Destination.x = m_Position.x;
}

void Projectile::UpdateAnimation()
{
	if (!m_Active) return;
	m_AnimStep >= 7 ? m_AnimStep = 0 : m_AnimStep++;
	m_Spritesheet.m_Source.x = 32 * m_AnimStep;
}

void Projectile::Draw()
{
	if (!m_Active) return;
	SDL_RenderCopy(Renderer::GetRenderer(), m_Spritesheet.m_Texture, &m_Spritesheet.m_Source, &m_Destination);
}

void ProjectileManager::Initialize(int no_of_projectiles)
{
	auto texture = Texture::LoadTexture("projectile.png");
	m_TextureData.m_Texture = texture.m_Texture;
	m_TextureData.m_Source = texture.m_Source;
	m_InactiveProjectiles = { Uint64(no_of_projectiles), Projectile(m_TextureData) };
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

void ProjectileManager::Activate(const SDL_FPoint& position)
{
	m_InactiveProjectiles.front().Activate(position);
	m_ActiveProjectiles.insert(m_ActiveProjectiles.end(), std::make_move_iterator(m_InactiveProjectiles.begin()),
		std::make_move_iterator(m_InactiveProjectiles.begin()+1));

	m_InactiveProjectiles.erase(begin(m_InactiveProjectiles), begin(m_InactiveProjectiles) + 1);
}