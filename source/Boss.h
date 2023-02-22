#pragma once
#include "Enemy.h"
#include <ai/Blackboard.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/composite/Sequence.h>

class Boss : public Enemy
{
public:
  Boss();

  void Initialize();
  void CreateBt();
#ifdef LOGGING
  void Input();
#endif // LOGGING

  void Update(const float delta_time);
  void UpdateAnimation();
  void UpdateAi(Vector2 goal);
  void Draw();

  void Death();
  void TakeDamage(unsigned short damage_amount);

private:
  ai::Blackboard    m_Blackboard;
  ai::FloatPtr      m_Timer;
  ai::FloatPtr      m_MeleeTimer;
  ai::FloatPtr      m_RangedTimer;
  ai::BehaviourTree m_Tree;
};
