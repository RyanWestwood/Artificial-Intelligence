#pragma once
#include <memory>
#include <fsm/StateManager.h>
#include <pathfinding/Path.h>
#include <math/Vector2.h>
#include <pathfinding/Node.h>
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

	AI::FSM::ManagerPtr m_FiniteStateMachine;
	AI::FSM::StatePtr m_AttackState;
	AI::FSM::StatePtr m_IdleState;

	std::vector<Vector2> m_Path;
	float m_MoveSpeed;
	float m_RotationSpeed;
	float m_StoppingDistance;
	SDL_FPoint m_GoalTile;
	AI::PATH::PathPtr m_SmoothedPath;
};