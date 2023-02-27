#include "Enemy.h"
#include "../engine/Pathing.h"
#include <algorithm>
#include <numeric>

Enemy::Enemy() :
  Entity()
{
  m_Health           = 100.f;
  m_MaxHealth        = 100.f;
  m_SearchAlgo       = pathing::Algo::A_Star;
  m_AvoidLayer       = ai::path::None;
  m_MovementSpeed    = 0.f;
  m_FollowingPath    = false;
  m_PathIndex        = 0;
  m_TurnDistance     = 5.f;
  m_TurnSpeed        = 5.f;
  m_StoppingDistance = 10.f;
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

  auto screen_dimensions = globals::GetScreenDimensions();
  m_Transform.Position.x = std::clamp(m_Transform.Position.x, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
  m_Transform.Position.y = std::clamp(m_Transform.Position.y, 0.f, screen_dimensions.h - 64.f); // Offsetting image size
}

void Enemy::FollowPath(float delta_time)
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
  m_Transform.Position = Vector2::MoveTowards(m_Transform.Position, current_waypoint, delta_time * m_MovementSpeed);
}

void Enemy::FollowSmoothedPath(const float delta_time)
{
  if(m_Path.empty()) return;

  Vector2 current_position = m_Transform.Position;
  float   speed_percentage = 1.f;

  if(m_FollowingPath)
  {
    while(m_SmoothedPath.m_TurnBoundaries[m_PathIndex].HasCrossedLine(current_position))
    {
      if(m_PathIndex == m_SmoothedPath.m_FinishLineIndex)
      {
        m_FollowingPath = false;
        return;
      }
      else
      {
        m_PathIndex++;
      }
    }
  }
  if(m_FollowingPath)
  {
    if(m_PathIndex >= m_SmoothedPath.m_SlowDownIndex && m_StoppingDistance > 0)
    {
      speed_percentage = std::clamp(m_SmoothedPath.m_TurnBoundaries[m_SmoothedPath.m_FinishLineIndex].DistanceFromPoint(current_position) / m_StoppingDistance, 0.0f, 1.0f);
      if(speed_percentage < 0.01f)
      {
        m_FollowingPath = false;
      }
    }
    auto goal_position        = m_SmoothedPath.m_LookPoints[m_PathIndex] * 32;
    auto target_rotation      = Vector2::GetAngleBetween(m_Transform.Position, goal_position);
    auto interpolate_rotation = std::lerp(m_Transform.Rotation, target_rotation, delta_time * m_TurnSpeed);
    auto clamped_rotation     = std::clamp(interpolate_rotation, -360.f, 360.f);
    m_Transform.Rotation      = clamped_rotation;
    m_Transform.Position.MoveForward(m_Transform.Rotation, delta_time * m_MovementSpeed);
  }
}

void Enemy::UpdateAnimation()
{
  Entity::UpdateAnimation();
}

void Enemy::UpdateAi(Vector2 goal)
{
  m_CachedStartPos = GetNodePosition();
  m_Path           = pathing::CreatePath(m_CachedStartPos, goal, m_SearchAlgo, m_AvoidLayer);
  m_SmoothedPath   = Path(m_Path, m_Transform.Position, 5, 5);
  m_FollowingPath  = true;
  m_PathIndex      = 0;
}

void Enemy::Draw()
{
  Entity::Draw();

  m_Image.Texture.Draw();
  m_HealthBar.Draw();
  m_AbilityBar.Draw();
  m_DisplayName.Draw();
}

bool Enemy::TakeDamage(float damage_amount)
{
  m_Health = std::clamp(m_Health - damage_amount, 0.f, m_MaxHealth);
  float percentage = (m_Health / m_MaxHealth) * 100.f;
  m_HealthBar.ChangeHealth((int)percentage);
  return m_Health <= 0;
}

void Enemy::Death()
{
}