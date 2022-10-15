#pragma once
#include <memory>
#include "fsm/StateManager.h"
#include "Dll.h"
#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();

	void Initialize();
	void Update(const float delta_time);
	void UpdateAnimation();
	void Draw();

public:
	int m_Ammo;
	float m_Timer;
	float m_Cooldown;

	AI::FSM::ManagerPtr m_FiniteStateMachine;
	AI::FSM::StatePtr m_AttackState;
	AI::FSM::StatePtr m_IdleState;
};