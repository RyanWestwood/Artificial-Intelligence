#pragma once
#include "Cooldown.h"
#include "Entity.h"
#include "Staff.h"
#include "Sword.h"
#include "Projectile.h"

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
	Cooldown m_MeleeCooldown;
	Cooldown m_RangedCooldown;
	std::shared_ptr<float> m_OffGlobal;
	std::shared_ptr<float> m_Global;
	Projectile m_Projectile;
};