#pragma once
#include <memory>
#include <fsm/StateManager.h>
#include <pathfinding/Pathfinding.h>
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
	void UpdateAi(SDL_Point goal);
	void Draw();
	void GoalTile();
	void Move(float delta_time);

public:
	int m_Ammo;
	float m_Timer;
	float m_Cooldown;

	AI::FSM::ManagerPtr m_FiniteStateMachine;
	AI::FSM::StatePtr m_AttackState;
	AI::FSM::StatePtr m_IdleState;

	std::vector<AI::PATH::Vector> m_Path;
	float m_MoveSpeed;
	SDL_FPoint m_GoalTile;
};