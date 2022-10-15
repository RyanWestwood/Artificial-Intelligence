#include "Enemy.h"
#include <algorithm>
#include "engine/Globals.h"

Enemy::Enemy()
{
	m_Ammo = 3;
	m_Timer = 1.f;
	m_Cooldown = 1.f;
	m_FiniteStateMachine = AI::FSM::GetStateManager();
	m_Position = { 256,256 };
	m_NoOfAnims = 7;

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

void Enemy::Initialize()
{
	Entity::Initialize();
	m_Sprite.Initialize("ad.png");
	m_Sprite.m_Source = { 0,0,32,32 };
	m_Sprite.m_Destination = { 128,128,64,64 };
	m_Collider = { 0,0,64,64 };
}
#ifdef LOGGING
void Enemy::Input()
{
	Entity::Input();
}
#endif // LOGGING

void Enemy::Update(const float delta_time)
{
	auto screen_dimensions = Globals::GetScreenDimensions();
	m_Position.x = std::clamp(m_Position.x + static_cast<float>(m_Velocity.x) * delta_time, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Position.y = std::clamp(m_Position.y + static_cast<float>(m_Velocity.y) * delta_time, -16.f, screen_dimensions.h - 64.f); // Offsetting image size
	m_Collider.x = m_Position.x;
	m_Collider.y = m_Position.y;
	m_Sprite.m_Destination.x = m_Position.x;
	m_Sprite.m_Destination.y = m_Position.y;

	m_Timer += delta_time;
	m_FiniteStateMachine->Update();
}

void Enemy::UpdateAnimation()
{
	Entity::UpdateAnimation();
}

void Enemy::Draw()
{
	Entity::Draw();
	m_Sprite.Draw();
}
