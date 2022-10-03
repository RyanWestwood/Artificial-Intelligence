#include "Enemy.h"

Enemy::Enemy()
{
	m_FiniteStateMachine = AI::FSM::GetStateManager();
	m_Ammo = 3;
	m_Timer = 1.f;
	m_Cooldown = 1.f;

	m_IdleState = AI::FSM::CreateState(m_FiniteStateMachine, [&]() {
		if (m_Timer >= 1.f) {
			std::cout << "Idle state\n";
			if (m_Timer >= m_Cooldown) {
				m_Timer = 0.f;
				m_FiniteStateMachine->SetState(m_AttackState);
			}
		}
	});

	m_AttackState = AI::FSM::CreateState(m_FiniteStateMachine, [&]() {
		if (m_Timer >= m_Cooldown) {
			if (m_Ammo <= 0) {
				std::cout << "Out of ammo, changing state to Idle!\n";
				m_Ammo = 3;
				m_FiniteStateMachine->SetState(m_IdleState);
			}
			else {
				std::cout << "Shoot\n";;
				m_Ammo--;
				if (m_Ammo % 10 == 0) {
					std::cout << "Ammo Count: " << m_Ammo << "\n";
				}
			}
			m_Timer = 0;
		}
	});

	m_FiniteStateMachine->SetState(m_AttackState);
}

void Enemy::Update(const float delta_time)
{
	m_Timer += delta_time;
	m_FiniteStateMachine->Update();
}

void Enemy::UpdateAnimation()
{

}