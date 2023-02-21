#include "Enemy.h"
#include "engine/Pathing.h"

Enemy::Enemy() :
  Entity()
{
  m_Health = 0;
  m_SearchAlgo = pathing::Algo::A_Star;
}

void Enemy::Initialize()
{
  Entity::Initialize();
}

#ifdef LOGGING
void Enemy::Input()
{
  Entity::Input();
}
#endif // LOGGING

void Enemy::Update(const float delta_time)
{
  m_Collider.Dimensions.x         = m_Transform.Position.x + m_Collider.PixelOffset.x;
  m_Collider.Dimensions.y         = m_Transform.Position.y + m_Collider.PixelOffset.y;
  m_Image.Texture.m_Destination.x = m_Transform.Position.x;
  m_Image.Texture.m_Destination.y = m_Transform.Position.y;
}

void Enemy::FollowPath(float movement_amount)
{
  if(m_Path.empty()) return;
  if(m_CachedStartPos == m_Path.front())
  {
    m_Path.erase(begin(m_Path));
    if(m_Path.empty()) return;
  }
  Vector2 current_waypoint = m_Path.front();
  current_waypoint.x *= 32;
  current_waypoint.y *= 32;

  if(m_Transform.Position == current_waypoint)
  {
    m_Path.erase(begin(m_Path));
    if(m_Path.empty()) return;

    current_waypoint = m_Path.front();
    current_waypoint.x *= 32;
    current_waypoint.y *= 32;
  }
  m_Transform.Position = Vector2::MoveTowards(m_Transform.Position, current_waypoint, movement_amount);
}

void Enemy::UpdateAnimation()
{
  Entity::UpdateAnimation();
}

void Enemy::UpdateAi(Vector2 goal)
{
  m_CachedStartPos = GetNodePosition();
  m_Path = pathing::CreatePath(m_CachedStartPos, goal, m_SearchAlgo, m_AvoidLayer);
}

void Enemy::Draw()
{
  Entity::Draw();

  m_Image.Texture.Draw();
  m_HealthBar.Draw();
  m_AbilityBar.Draw();
  m_DisplayName.Draw();
}

void Enemy::TakeDamage(unsigned short damage_amount)
{
}

void Enemy::Death()
{
}

