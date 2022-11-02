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
	m_Position = { 736,256 };
	m_NoOfAnims = 7;
	m_Collider = { 6,4,50,56 };
	m_ColliderOffset = { 6,4 };
	m_Velocity = { 0,0 };
	m_MoveSpeed = 32.f;
	m_GoalTile = { 0,0 };
	m_SmoothedPath = AI::PATH::CreatePath();

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
	//Move(delta_time);
	if (!m_SmoothedPath->m_LookPoints.empty()) {
		FollowSmoothedPath(delta_time);
	}

	m_Position.x = std::clamp(m_Position.x, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Position.y = std::clamp(m_Position.y, -16.f, screen_dimensions.h - 64.f); // Offsetting image size
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
	m_SmoothedPath->UpdatePath(m_Path, { m_Position.x / 32 + 1, m_Position.y / 32 + 1 }, 5.f); // TODO: fix this.
	GoalTile();
}

void Enemy::Draw()
{
	Entity::Draw();
	m_Sprite.Draw();
}

void Enemy::GoalTile()
{
	if(m_Path.size() <= 1) return;
	auto current_position = { (int)m_Position.x / 32 + 1, (int)m_Position.y / 32 + 1 };
	m_GoalTile = SDL_FPoint{ (float)m_Path[1].x, (float)m_Path[1].y };
}

void Enemy::Move(const float delta_time)
{
	if (m_GoalTile.x == 0.f && m_GoalTile.y == 0.f) return;

	SDL_FPoint GreenBox = { (int)m_Position.x / 32 + 1, (int)m_Position.y / 32 + 1 };
	SDL_FPoint Difference = { m_GoalTile.x - GreenBox.x, m_GoalTile.y - GreenBox.y };
	m_Position.x += Difference.x;
	m_Position.y += Difference.y;
}

void Enemy::FollowSmoothedPath(const float delta_time)
{
	bool following_path = true;
	int path_index = 0;
	//	TODO: Transform look at!

	while(following_path){
		Vector2 position_2d = { m_Position.x, m_Position.y };
		if(m_SmoothedPath->m_TurnBoundaries[path_index].HasCrossedLine(position_2d)){
			if(path_index == m_SmoothedPath->m_FinishLineIndex){ // TODO: This is returning -1?
				following_path = false;
			} else {
				path_index++;
			}
		}

		if(following_path){
			Vector2 dir = { m_SmoothedPath->m_LookPoints[path_index] - m_Position };
			const float angle_radians = std::atan2f(dir.y, dir.x);
			const float angle_degrees = angle_radians * (180.0 / 3.141592653589793238463);
			const float rotation_speed = .1f;
			const float move_speed = 5.f;
			m_Rotation = std::lerp(m_Rotation, angle_degrees, delta_time * rotation_speed);
			//Move(Vector2.forwards * move_speed * delta_time);
		}
	}
}