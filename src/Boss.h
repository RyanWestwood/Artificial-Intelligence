#pragma once
#include "engine/font.h"
#include "Entity.h"
#include "ui/AbilityBar.h"
#include "ui/Healthbar.h"
#include "Blackboard.h"
#include "bt/BehaviorTree.h"
#include "bt/composite/Sequence.h"

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

	void Death() {}
	void TakeDamage(unsigned short damage_amount)
	{
		m_Health -= damage_amount;
		if (m_Health <= 0) {
			Death();
		}
		m_HealthBar.ChangeHealth(m_Health);
	}

private:
	Text m_DisplayName;
	HealthBar m_HealthBar;
	AbilityBar m_AbilityBar;
	int m_Health;

	ai::BlackboardPtr m_Blackboard;
	ai::FloatPtr m_Timer;
	ai::bt::BehaviourTree m_Tree;
};