#pragma once
#include "Cooldown.h"
#include "Entity.h"
#include "Staff.h"
#include "Sword.h"

enum class Direction {
	North = 0,
	South,
	East,
	West,
	None
};

class Player : public Entity {
public: 
	Player();

	void Initialize();
	void KeyUp(SDL_Scancode code, const char* message);

	void Input() override;
	void Update(const float delta_time) override;
	void Resume();
	void UpdateAnimation() override;
	void Draw() override;

	void HealthSpell(){}
	void Mitigation(){}

public:
	Sword m_Sword;
	Cooldown m_MeleeCooldown;
	Cooldown m_RangedCooldown;
	Cooldown m_HealthRegenCooldown;
	Cooldown m_MitigationCooldown;
	std::shared_ptr<float> m_OffGlobal;
	std::shared_ptr<float> m_Global;
	Direction m_Facing;
};