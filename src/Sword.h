#pragma once
#include <vector>
#include "Attack.h"
#include "Projectile.h"

class Sword : public Attack{
public:
	Sword();

	void Initialize(const char* filename, std::shared_ptr<float> timer);
	void Update(const float& delta_time, const SDL_FPoint position);
	void Draw(const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void Swing();
	void Fire();

private:
	bool m_FireAction;
	SDL_FPoint m_FireOffset;
	std::vector<Projectile> m_Projectile;

	int m_Temp;
};