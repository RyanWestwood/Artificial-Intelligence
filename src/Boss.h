#pragma once
#include "engine/font.h"
#include "Entity.h"
#include "ui/AbilityBar.h"
#include "ui/Healthbar.h"

class Boss : public Entity {
public:
	Boss();

	void Initialize();
#ifdef LOGGING
	void Input();
#endif // LOGGING

	void Update(const float delta_time);
	void UpdateAnimation();
	void UpdateAi(Vector2 goal);
	void Draw();

private:
	Text m_DisplayName;
	HealthBar m_HealthBar;
	AbilityBar m_AbilityBar;
	int m_Health;
};