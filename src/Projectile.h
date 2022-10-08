#pragma once
#include <vector>
#include "engine/Texture.h"
#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile(Texture::TextureData spritesheet);

	void Update(const float& delta_time);
	void UpdateAnimation();
	void Draw();
	void Activate(SDL_FPoint position);
public:
	bool m_Active;

private:
	Texture::TextureData m_Spritesheet;
	SDL_Rect m_Destination;
};

class ProjectileManager{
public:
	ProjectileManager(){}

	void Initialize(int no_of_projectiles);
	void Update(const float& delta_time);
	void UpdateAnimation();
	void Draw();

	void Activate(const SDL_FPoint& position);
public:
	std::vector<Projectile> m_Projectiles;
	Texture::TextureData m_TextureData;
};