#pragma once
#include "Entity.h"

class Player : public Entity {
public: 
	Player();

	void Initialize();

	void Input() override;
	void Update(float delta_time) override;
	void UpdateAnimation() override;
	void Draw() override;
};