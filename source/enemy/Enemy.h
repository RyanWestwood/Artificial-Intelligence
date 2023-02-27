#pragma once
#include "../engine/Font.h"
#include "../engine/Pathing.h"
#include "../Entity.h"
#include "../ui/AbilityBar.h"
#include "../ui/Healthbar.h"
#include <ai/math/Vector2.h>
#include <ai/pf/Node.h>
#include <ai/pf/Path.h>
#include <vector>

using ai::path::Obstacle;
using ai::path::Path;

class Enemy : public Entity
{
public:
  Enemy();

  virtual void Initialize();
#ifdef LOGGING
  void Input();
#endif // LOGGING

  virtual void Update(const float delta_time);
  virtual void UpdateAnimation();
  virtual void UpdateAi(Vector2 goal);
  virtual void Draw();

  virtual void TakeDamage(unsigned short damage_amount);
  virtual void Death();
  virtual void FollowPath(const float delta_time);
  virtual void FollowSmoothedPath(const float delta_time);

public:
  Text       m_DisplayName;
  HealthBar  m_HealthBar;
  AbilityBar m_AbilityBar;
  int        m_Health;

  float                m_MovementSpeed;
  std::vector<Vector2> m_Path;
  Vector2              m_CachedStartPos;
  Obstacle             m_AvoidLayer;
  pathing::Algo        m_SearchAlgo;

  // Updating to smoothed
  bool  m_FollowingPath;
  float m_TurnDistance;
  float m_TurnSpeed;
  float m_StoppingDistance;
  int   m_PathIndex;
  Path  m_SmoothedPath;
};
