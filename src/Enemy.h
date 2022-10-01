#pragma once
#include <memory>
#include "fsm/StateManager.h"
#include "Dll.h"
#include "Entity.h"

typedef AI::FSM::Function  Function;
typedef std::shared_ptr<AI::FSM::StateManager> FsmPtr;
typedef std::shared_ptr<AI::FSM::State> StatePtr;

class Enemy : public Entity {
public:
	Enemy();

	void Update(float delta_time);
	void UpdateAnimation();
	void Draw();

public:
	FsmPtr m_FiniteStateMachine;
	int m_Ammo;
	float m_Timer;
	float m_Cooldown;
};