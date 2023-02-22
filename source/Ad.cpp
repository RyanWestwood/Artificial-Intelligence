#include "Ad.h"
#include "engine/Globals.h"
#include "engine/Pathing.h"
#include <algorithm>
#include <cmath>
#include <random>

Ad::Ad() :
  Enemy()
{
  m_Collider.Dimensions     = {6, 4, 50, 56};
  m_Collider.PixelOffset    = {6, 4};
  m_Transform.Position      = {736, 256};
  m_Transform.Velocity      = {32.f, 32.f};
  m_Transform.RotationSpeed = .5f;
  m_Image.NoOfAnims         = 7;
  m_Health                  = 100;
  m_MovementSpeed           = 64.f;
  m_AvoidLayer              = ai::path::Boss;

  CreateEnemyFsm();
  CreateAttackFsm();
  m_RunningFsm = m_EnemyFsm;
}

void Ad::Initialize()
{
  Entity::Initialize();
  m_Image.Texture.Initialize("ad.png");
  m_Image.Texture.m_Source      = {0, 0, 32, 32};
  m_Image.Texture.m_Destination = {128, 128, 64, 64};

  m_Blackboard = ai::CreateBlackboard(globals::GetAssetDirectory() + "blackboards/ad.csv");
  m_Cooldown   = m_Blackboard->GetFloat("basic_cooldown", 3.f);
  m_Timer      = m_Blackboard->GetFloat("update_timer", 1.f);
  m_Ammo       = m_Blackboard->GetInt("ammo_size", 3);

  m_HealthBar.Initialize({468, 30, 600, 24}, 4);
  m_AbilityBar.Initialize({764, 70, 300, 12}, 2, "TACTICAL REMOVER");

  m_DisplayName.Initalize("BOB, DESTROYER OF WORLDS");
  m_DisplayName.m_Dimensions.x = 590;
  m_DisplayName.m_Dimensions.y = 10;
}

#ifdef LOGGING
void Ad::Input()
{
  Entity::Input();
}
#endif // LOGGING

void Ad::Update(const float delta_time)
{
  Enemy::Update(delta_time);
  Enemy::FollowPath(delta_time);

  //*m_Timer += delta_time;
  //m_RunningFsm->Update(delta_time);
}

void Ad::UpdateAnimation()
{
  Entity::UpdateAnimation();
}

void Ad::UpdateAi(Vector2 goal)
{
  Enemy::UpdateAi(goal);
}

void Ad::Draw()
{
  Enemy::Draw();
}

void Ad::TakeDamage(unsigned short damage_amount)
{
  m_Health -= damage_amount;
  if(m_Health <= 0)
  {
    Death();
  }
  m_HealthBar.ChangeHealth(m_Health);
}

void Ad::Death()
{
  m_RunningFsm = m_EnemyFsm;
  m_EnemyFsm->SetState(m_DieState);
}

void Ad::CreateEnemyFsm()
{
  m_EnemyFsm = ai::fsm::GetStateManager();

  m_IdleState = ai::fsm::CreateState(m_EnemyFsm, "Idle", [&](const float delta_time) {
    if(*m_Timer >= 2.f)
    {
      *m_Timer = 0.f;
#ifdef LOGGING
      std::cout << "Idle state finished\nSwitching to wander state\n";
#endif // LOGGING
      m_EnemyFsm->SetState(m_WanderState);
      *m_Ammo = 3;
    }
  });

  m_WanderState = ai::fsm::CreateState(m_EnemyFsm, "Wander", [&](const float delta_time) {
    if(*m_Timer >= 1.f)
    {
      *m_Timer = 0;
#ifdef LOGGING
      std::cout << "Wander state finished\nSwitching to attack state\n";
#endif // LOGGING
      m_RunningFsm = m_AttackFsm;
      m_EnemyFsm->SetState(m_IdleState);
    }
  });

  m_DieState = ai::fsm::CreateState(m_EnemyFsm, "Die", [&](const float delta_time) {
    if(*m_Timer >= 1.f)
    {
      *m_Timer = 0;
#ifdef LOGGING
      std::cout << "Die state finished\nFSM STOPPED\n";
#endif // LOGGING
      m_EnemyFsm->KillManager();
    }
  });

  m_SpawnState = ai::fsm::CreateState(m_EnemyFsm, "Spawn", [&](const float delta_time) {
    if(*m_Timer >= 2.f)
    {
      *m_Timer = 0;
#ifdef LOGGING
      std::cout << "Spawn state finished\nSwitching to idle state\n";
#endif // LOGGING
      m_EnemyFsm->SetState(m_IdleState);
    }
  });

  m_EnemyFsm->SetState(m_SpawnState);
}

void Ad::CreateAttackFsm()
{
  m_AttackFsm = ai::fsm::GetStateManager();

  m_AttackEntryState = ai::fsm::CreateState(m_AttackFsm, "Attack Entry Point", [&](const float delta_time) {
    if(*m_Timer >= 1.f)
    {
      *m_Timer = 0;
      std::random_device                 dev;
      std::mt19937                       rng(dev());
      std::uniform_int_distribution<int> distribution(0, 99);
      int                                probability   = 50;
      int                                random_number = distribution(rng);
#ifdef LOGGING
      std::cout << "Entry state - ";
#endif // LOGGING
      if(random_number < probability)
      {
#ifdef LOGGING
        std::cout << "Chose ranged state! (" << random_number << ")\n";
#endif // LOGGING
        m_AttackFsm->SetState(m_RangedAttackState);
      }
      else
      {
#ifdef LOGGING
        std::cout << "Chose melee state! (" << random_number << ")\n";
#endif // LOGGING
        m_AttackFsm->SetState(m_MeleeAttackState);
      }
    }
  });

  m_RangedAttackState = ai::fsm::CreateState(m_AttackFsm, "Ranged Attack", [&](const float delta_time) {
    if(*m_Timer >= 1.f)
    {
      *m_Timer = 0;
#ifdef LOGGING
      std::cout << "Shoot state - shooting\n";
#endif // LOGGING
      if(*m_Ammo <= 0)
      {
#ifdef LOGGING
        std::cout << "Shoot state - out of ammo\nSwitch to idle state\n";
#endif // LOGGING
        *m_Ammo      = 3;
        //m_GoalTile   = {0.f, 0.f};
        m_RunningFsm = m_EnemyFsm;
        m_AttackFsm->SetState(m_AttackEntryState);
      }
      else
      {
#ifdef LOGGING
        std::cout << "Shoot state - shoot\t " << *m_Ammo - 1 << " shots remaining"
                  << "\n";
#endif // LOGGING
        *m_Ammo = *m_Ammo - 1;
        // TODO: Damage player with ranged procteile here!
        //GoalTile();
      }
    }
  });

  m_MeleeAttackState = ai::fsm::CreateState(m_AttackFsm, "Melee Attack", [&](const float delta_time) {
    if(*m_Timer >= 3.f)
    {
      *m_Timer = 0;
#ifdef LOGGING
      std::cout << "Melee state - attacking\n";
#endif // LOGGING
      //m_GoalTile   = {0.f, 0.f};
      m_RunningFsm = m_EnemyFsm;
      // TODO: Damage player with melee based damage from here.
      m_AttackFsm->SetState(m_AttackEntryState);
    }
  });

  m_AttackFsm->SetState(m_AttackEntryState);
}
