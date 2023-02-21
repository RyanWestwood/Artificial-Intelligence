#pragma once
#include "Enemy.h"
#include <ai/Blackboard.h>
#include <ai/fsm/StateManager.h>
#include <ai/math/Vector2.h>
#include <memory>

class Ad : public Enemy
{
public:
  Ad();

  void Initialize();
#ifdef LOGGING
  void Input();
#endif // LOGGING

  void Update(const float delta_time);
  void UpdateAnimation();
  void UpdateAi(Vector2 goal);
  void Draw();

  void TakeDamage(unsigned short damage_amount);
  void Death();

private:
  void CreateEnemyFsm();
  void CreateAttackFsm();

public:
  ai::IntPtr   m_Ammo;
  ai::FloatPtr m_Timer;
  ai::FloatPtr m_Cooldown;

  ai::fsm::ManagerPtr m_EnemyFsm;
  ai::fsm::ManagerPtr m_AttackFsm;
  ai::fsm::ManagerPtr m_RunningFsm;
  ai::BlackboardPtr   m_Blackboard;

  ai::fsm::StatePtr m_DieState;
  ai::fsm::StatePtr m_SpawnState;
  ai::fsm::StatePtr m_IdleState;
  ai::fsm::StatePtr m_WanderState;

  ai::fsm::StatePtr m_AttackEntryState;
  ai::fsm::StatePtr m_MeleeAttackState;
  ai::fsm::StatePtr m_RangedAttackState;
};
