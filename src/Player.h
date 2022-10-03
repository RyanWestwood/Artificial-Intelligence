#pragma once
#include "Entity.h"
#include "Sword.h"

class Player : public Entity {
public: 
	Player();

	void Initialize();

	void Input() override;
	void Update(float delta_time) override;
	void UpdateAnimation() override;
	void Draw() override;

public:
	Sword m_Sword;

};