#include "Boss.h"
#include "../engine/Globals.h"
#include "../engine/Pathing.h"
#include <ai/bt/NodeFactory.h>

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

  // CreateBt();
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
  // m_Tree.Update();
  //*m_Timer += delta_time;
  //*m_RangedTimer -= delta_time;
  //*m_MeleeTimer -= delta_time;
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
  m_Health -= damage_amount;
  if(m_Health <= 0)
  {
    Death();
  }
  m_HealthBar.ChangeHealth(m_Health);
}

void Boss::CreateBt()
{
  auto death = [&]() -> Status {
    if(m_Health <= 0)
    {
      Death();
#ifdef LOGGING
      std::cout << "Died in the behavior tree!\n";
#endif
      return Status::Success;
    }
    return Status::Running;
  };

  auto melee = [&]() -> Status {
    if(*m_Timer >= 1.f && *m_MeleeTimer <= 0.f)
    {
      std::cout << "Melee Attack!\n";
      *m_Timer      = 0.f;
      *m_MeleeTimer = 2.f;
      return Status::Success;
    }
    return Status::Running;
  };

  auto range = [&]() -> Status {
    if(*m_Timer >= 1.f && *m_RangedTimer <= 0.f)
    {
      std::cout << "Ranged Attack!\n";
      *m_Timer       = 0.f;
      *m_RangedTimer = 2.f;
      return Status::Success;
    }
    return Status::Running;
  };

  auto sequence = NodeFactory::createCompositeNode<Sequence>(m_Blackboard);
  auto action1  = NodeFactory::createNode<Node>(m_Blackboard, death);
  auto action2  = NodeFactory::createNode<Node>(m_Blackboard, melee);
  auto action3  = NodeFactory::createNode<Node>(m_Blackboard, range);

  sequence->AddNode(std::move(action2));
  sequence->AddNode(std::move(action3));
  m_Tree = ai::BehaviourTree(std::move(sequence));
}
