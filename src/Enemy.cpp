#include "Enemy.h"
#include <algorithm>
#include <cmath>
#include "engine/Globals.h"
#include "engine/Pathing.h"

Enemy::Enemy() : Entity()
{
	m_Ammo = 3;
	m_Timer = 1.f;
	m_Cooldown = 1.f;
	m_FiniteStateMachine = AI::FSM::GetStateManager();
	m_Position = { 256,256 };
	m_NoOfAnims = 7;
	m_Collider = { 6,4,50,56 };
	m_ColliderOffset = { 6,4 };
	m_Velocity = { 0,0 };
	m_MoveSpeed = 32.f;

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

	FollowPath(delta_time);

	std::cout << current_position.x << ", " << current_position.y << "\n";
	m_Position.x = std::clamp(m_Position.x, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Position.y = std::clamp(m_Position.y, -16.f, screen_dimensions.h - 64.f); // Offsetting image size
	std::cout << current_position.x << ", " << current_position.y << "\n";
	m_Collider.x = m_Position.x + m_ColliderOffset.x;
	m_Collider.y = m_Position.y + m_ColliderOffset.y;
	m_Sprite.m_Destination.x = m_Position.x;
	m_Sprite.m_Destination.y = m_Position.y;

	m_Timer += delta_time;
	m_FiniteStateMachine->Update();
}

void Enemy::UpdateAnimation()
{
	Entity::UpdateAnimation();
}

void Enemy::UpdateAi(SDL_Point goal)
{
	std::cout << "Update AI\n";
	m_Path = PATHING::CreatePath({ (int)m_Position.x / 32 + 1, (int)m_Position.y / 32 + 1 }, goal, PATHING::Algo::A_Star);
}

void Enemy::Draw()
{
	Entity::Draw();
	m_Sprite.Draw();
}

void Enemy::MoveTowards(SDL_FPoint current, SDL_FPoint target, float maxDistanceDelta)
{
	SDL_FPoint a = { target.x - current.x, target.y - current.y };
	float magnitude = sqrtf((a.x * a.x) + (a.y * a.y));
	if (magnitude <= maxDistanceDelta || magnitude == 0.f)
	{
		return;
	}

	SDL_FPoint b = { a.x / magnitude * maxDistanceDelta, a.y / magnitude * maxDistanceDelta };
	m_Position.x += b.x;
	m_Position.y += b.y;
}

bool AreSame(SDL_FPoint lhs, SDL_FPoint rhs)
{
	auto x = fabs(lhs.x - rhs.x);
	auto y = fabs(lhs.y - rhs.y);
	float epsilion = 0.25f;
	return x < epsilion && y < epsilion;
}

void Enemy::FollowPath(const float delta_time)
{
	if (m_Path.empty()) return;
	SDL_FPoint current_waypoint = { m_Path.front().x * 32, m_Path.front().y * 32 };
	SDL_FPoint current_position = { m_Position.x + 32, m_Position.y + 32};
	int target_index = 0;

	if (AreSame(current_position, current_waypoint)) {
		target_index++;
		if (target_index >= m_Path.size()) {
			return;
		}
		current_waypoint = { (float)m_Path.at(target_index).x * 32, (float)m_Path.at(target_index).y * 32 };
	}
	MoveTowards(current_position, current_waypoint, m_MoveSpeed * delta_time);
}