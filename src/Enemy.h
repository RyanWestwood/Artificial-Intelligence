#pragma once
#include <memory>
#include <fsm/StateManager.h>
#include <pathfinding/Node.h>
#include <pathfinding/Path.h>
#include <math/Vector2.h>
#include <Blackboard.h>
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
	void GoalTile();
	void Move(const float delta_time);
	void FollowSmoothedPath(const float delta_time);

public:
	int m_Ammo;
	float m_Timer;
	float m_Cooldown;

	ai::BlackboardPtr m_Blackboard;
	ai::fsm::ManagerPtr m_FiniteStateMachine;
	ai::fsm::StatePtr m_AttackState;
	ai::fsm::StatePtr m_IdleState;
	ai::fsm::StatePtr m_WonderState;

	std::vector<Vector2> m_Path;
	float m_MoveSpeed;
	float m_RotationSpeed;
	float m_StoppingDistance;
	SDL_FPoint m_GoalTile;
	ai::path::PathPtr m_SmoothedPath;
};