#include "Enemy.h"

Enemy::Enemy()
{
	m_FiniteStateMachine = AI::FSM::GetStateManager();
	m_Ammo = 10;
	m_Timer = 1.f;
	m_Cooldown = 1.f;

	AI::FSM::Function attack = [&]() {
		if (m_Timer >= m_Cooldown) {
			if (m_Ammo <= 0) {
				std::cout << "Out of ammo, changing state to null..." << std::endl;
				m_FiniteStateMachine->SetState(nullptr);
			}
			else {
				std::cout << "Shoot" << std::endl;
				m_Ammo--;
				if (m_Ammo % 10 == 0) {
					std::cout << "Ammo Count: " << m_Ammo << std::endl;
				}
			}
			m_Timer = 0;
		}
	};

	AI::FSM::StatePtr attackstate = AI::FSM::CreateState(m_FiniteStateMachine, attack);
	m_FiniteStateMachine->SetState(std::move(attackstate));
}

void Enemy::Update(float delta_time)
{
	m_Timer += delta_time;
}

void Enemy::UpdateAnimation()
{
	m_FiniteStateMachine->Update();
}