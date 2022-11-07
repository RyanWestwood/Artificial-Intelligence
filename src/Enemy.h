#pragma once
#include <memory>
#include <fsm/StateManager.h>
#include <pathfinding/Node.h>
#include <pathfinding/Path.h>
#include <math/Vector2.h>
#include "Entity.h"

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

	void Death();
	void GoalTile();
	void Move(const float delta_time);
	void FollowSmoothedPath(const float delta_time);

public:
	int m_Ammo;
	float m_Timer;
	float m_Cooldown;

	ai::fsm::ManagerPtr m_EnemyFSM;
	ai::fsm::ManagerPtr m_AttackFSM;
	ai::fsm::ManagerPtr m_RunningFSM;
	ai::fsm::StatePtr m_AttackState;
	ai::fsm::StatePtr m_DieState;
	ai::fsm::StatePtr m_SpawnState;
	ai::fsm::StatePtr m_IdleState;
	ai::fsm::StatePtr m_WanderState;

	std::vector<Vector2> m_Path;
	float m_StoppingDistance;
	Vector2 m_GoalTile;
	ai::path::PathPtr m_SmoothedPath;
};