#pragma once
#include "Entity.h"

class Player : public Entity {
public: 
	Player();

	void Initialize();

	void Input() override;
	void Update(double delta_time) override;
	void Draw() override;
};