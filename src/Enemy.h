#pragma once
#include <memory>
#include <ai/fsm/StateManager.h>
#include <ai/pathfinding/Node.h>
#include <ai/pathfinding/Path.h>
#include <ai/math/Vector2.h>
#include <ai/Blackboard.h>
#include "engine/font.h"
#include "Entity.h"
#include "ui/AbilityBar.h"
#include "ui/Healthbar.h"

class Enemy : public Entity {
public:
	Enemy();

	void Initialize();
#ifdef LOGGING
	void Input();
#endif // LOGGING

	void Update(const float delta_time);
	void UpdateAnimation();
	void UpdateAi(Vector2 goal);
	void Draw();

	void TakeDamage(unsigned short damage_amount);
	void Death();
	void GoalTile();
	void Move(const float delta_time);
	void FollowSmoothedPath(const float delta_time);

private:
	void CreateEnemyFsm();
	void CreateAttackFsm();

public:
	Text m_DisplayName;
	HealthBar m_HealthBar;
	AbilityBar m_AbilityBar;
	int m_Health;

	ai::IntPtr m_Ammo;
	ai::FloatPtr m_Timer;
	ai::FloatPtr m_Cooldown;

	ai::fsm::ManagerPtr m_EnemyFsm;
	ai::fsm::ManagerPtr m_AttackFsm;
	ai::fsm::ManagerPtr m_RunningFsm;
	ai::BlackboardPtr m_Blackboard;
  
	ai::fsm::StatePtr m_DieState;
	ai::fsm::StatePtr m_SpawnState;
	ai::fsm::StatePtr m_IdleState;
	ai::fsm::StatePtr m_WanderState;

	ai::fsm::StatePtr m_AttackEntryState;
	ai::fsm::StatePtr m_MeleeAttackState;
	ai::fsm::StatePtr m_RangedAttackState;

	std::vector<Vector2> m_Path;
	float m_StoppingDistance;
	Vector2 m_GoalTile;
	ai::path::PathPtr m_SmoothedPath;
};