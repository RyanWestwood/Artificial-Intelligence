#pragma once
#include "Cooldown.h"
#include "Entity.h"
#include "Staff.h"
#include "Sword.h"

class Player : public Entity {
public: 
	Player();

	void Initialize();

	void Input() override;
	void Update(const float delta_time) override;
	void Resume();
	void UpdateAnimation() override;
	void Draw() override;

public:
	Sword m_Sword;
	Staff m_Staff;
	Cooldown m_MeleeCooldown;
	Cooldown m_RangedCooldown;
};