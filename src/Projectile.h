#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile();

	void Initialize();
	void Update(const float delta_time);
	void UpdateAnimation();
	void Draw();
public:

};