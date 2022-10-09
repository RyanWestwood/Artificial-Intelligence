#pragma once
#include <functional>
#include <vector>
#include "engine/Texture.h"
#include "Entity.h"

class Projectile;
class ProjectileManager {
public:
	ProjectileManager() {}

	void Initialize(int no_of_projectiles);
	void Update(const float& delta_time);
	void UpdateAnimation();
	void Draw();

	void Activate(const SDL_FPoint& position);
	void Deactivate(Projectile& projectile);
public:
	std::vector<Projectile> m_InactiveProjectiles;
	std::vector<Projectile> m_ActiveProjectiles;
	Texture::TextureData m_TextureData;
};

class Projectile : public Entity {
public:
	Projectile(Texture::TextureData spritesheet, ProjectileManager* manager);

	void Update(const float& delta_time);
	void UpdateAnimation();
	void Draw();
	void Activate(SDL_FPoint position);
	void Deactivate();
private:
	bool m_Active;
	Texture::TextureData m_Spritesheet;
	SDL_Rect m_Destination;
	ProjectileManager* m_Manager;
};