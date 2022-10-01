#pragma once
#include <memory>
#include "fsm/StateManager.h"
#include "Dll.h"
#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();

	void Update(float delta_time);
	void UpdateAnimation();
	void Draw();

public:
	std::shared_ptr<AI::FSM::StateManager> m_FiniteStateMachine;
	int m_Ammo;
	float m_Timer;
	float m_Cooldown;
};