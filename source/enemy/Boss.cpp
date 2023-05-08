#include "Boss.h"
#include "../engine/Globals.h"
#include "../engine/Pathing.h"
#include "../engine/Utils.h"
#include <ai/bt/NodeFactory.h>
#include <algorithm>

Boss::Boss() :
  Enemy()
{
  m_Collider.Dimensions  = {6, 4, 50, 56};
  m_Collider.PixelOffset = {6, 4};
  m_Transform.Position   = {768, 712};
  m_Transform.Velocity   = {32.f, 32.f};
  m_Image.NoOfAnims      = 7;
  m_Health               = 100.f;
  m_MaxHealth            = 100.f;
  m_MovementSpeed        = 64.f;
  m_AvoidLayer           = ai::path::Ad;
}

void Boss::Initialize()
{
  Entity::Initialize();
  m_Image.Texture.Initialize("ad.png");
  m_Image.Texture.m_Source      = {0, 0, 32, 32};
  m_Image.Texture.m_Destination = {128, 128, 64, 64};

  m_HealthBar.Initialize({468, 30, 600, 24}, 4);
  m_AbilityBar.Initialize({764, 70, 300, 12}, 2, "TACTICAL DESTROYER");

  m_DisplayName.Initalize("PAUL, DESTROYER OF PLANETS");
  m_DisplayName.m_Dimensions.x = 590;
  m_DisplayName.m_Dimensions.y = 10;

  m_Blackboard  = ai::Blackboard(globals::GetAssetDirectory() + "blackboards/boss.csv");
  m_Timer       = m_Blackboard.GetFloat("update_timer", 1.f);
  m_MeleeTimer  = m_Blackboard.GetFloat("melee_timer", 2.f);
  m_RangedTimer = m_Blackboard.GetFloat("ranged_timer", 2.f);

  CreateBt();
}

#ifdef LOGGING
void Boss::Input()
{
  Entity::Input();
}
#endif // LOGGING

void Boss::Update(const float delta_time)
{
  Enemy::FollowPath(delta_time);

  Enemy::Update(delta_time);

  m_Tree.Update();
  *m_Timer += delta_time;
  *m_RangedTimer -= delta_time;
  *m_MeleeTimer -= delta_time;
}

void Boss::UpdateAnimation()
{
  Entity::UpdateAnimation();
}

void Boss::UpdateAi(Vector2 goal)
{
  Enemy::UpdateAi(goal);
}

void Boss::Draw()
{
  Enemy::Draw();
}

void Boss::Death()
{
}

void Boss::TakeDamage(unsigned short damage_amount)
{
  Enemy::TakeDamage(damage_amount);
}

void Boss::CreateBt()
{
  auto alive_action = [&]() -> Status {
    if(m_Health <= 0)
    {
      Death();
#ifdef LOGGING
      std::cout << "Died in the behavior tree!\n";
#endif
      return Status::Failure;
    }
    return Status::Success;
  };

  auto reset_action = [&]() -> Status {
    tree_conditions.reset();
    return Status::Running;
  };

  auto melee = [&]() -> Status {
    if(tree_conditions[0]) return Status::Success;
    // std::cout << "Counting down Melee Attack!\n";
    m_AbilityBar.ChangeName("MELEE ATTACK");
    m_AbilityBar.ChangeProgress((*m_MeleeTimer / 2.f) * 100);
    if(*m_Timer >= 2.f && *m_MeleeTimer <= 0.f)
    {
#ifdef LOGGING
      std::cout << "Melee Attack!\n";
#endif
      utils::GetPlayer().TakeDamage(10.f);
      *m_Timer       = 0.f;
      *m_MeleeTimer  = 2.f;
      *m_RangedTimer = 2.f;
      tree_conditions.set(0);
      return Status::Success;
    }
    return Status::Running;
  };

  auto raid_wide = [&]() -> Status {
    // std::cout << "Counting down Ranged Attack!\n";
    if(tree_conditions[1]) return Status::Success;
    m_AbilityBar.ChangeName("RANGED ATTACK");
    m_AbilityBar.ChangeProgress((*m_RangedTimer / 2.f) * 100);
    if(*m_Timer >= 2.f && *m_RangedTimer <= 0.f)
    {
#ifdef LOGGING
      std::cout << "RaidWide Attack!\n";
#endif
      utils::GetPlayer().TakeDamage(5.f);
      *m_Timer       = 0.f;
      *m_RangedTimer = 2.f;
      *m_MeleeTimer  = 2.f;
      tree_conditions.set(1);
      return Status::Running; // TODO; Change this back to success when finshed.
    }
    return Status::Running;
  };

  auto sequence         = NodeFactory::createCompositeNode<Sequence>(m_Blackboard);
  auto melee_action     = NodeFactory::createNode<Node>(m_Blackboard, melee);
  auto raid_wide_action = NodeFactory::createNode<Node>(m_Blackboard, raid_wide);
  auto check_alive      = NodeFactory::createNode<Node>(m_Blackboard, alive_action);
  auto reset_actions    = NodeFactory::createNode<Node>(m_Blackboard, reset_action);

  sequence->AddNode(std::move(check_alive));
  sequence->AddNode(std::move(melee_action));
  sequence->AddNode(std::move(raid_wide_action));
  sequence->AddNode(std::move(reset_actions));
  m_Tree = ai::BehaviourTree(std::move(sequence));
}
