#pragma once
#include "Attack.h"

class Sword : public Attack{
public:
	Sword();

	void Initialize(const char* filename, std::shared_ptr<float> timer);
	void Update(const float& delta_time, const SDL_FPoint position);
	void Draw(const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void Swing();
};