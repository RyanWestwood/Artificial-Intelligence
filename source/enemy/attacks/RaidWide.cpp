#include "RaidWide.h"

RaidWide::RaidWide() :
  Entity()
{
  m_Damage = 10.f;
}

void RaidWide::Initialize()
{
  Entity::Initialize();

  m_Image.Texture.Initialize("explosions.png");
  m_Image.Texture.m_Source      = {0, 0, 64, 64};
  m_Image.Texture.m_Destination = {128, 128, 96, 96};
  m_Image.NoOfAnims             = 8;
}

void RaidWide::Activate()
{
  m_Active = true;
}

void RaidWide::Deactivate()
{
  m_Active = false;
}

void RaidWide::Draw()
{
  if(!m_Active) return;

  Entity::Draw();
  m_Image.Texture.Draw();
}

void RaidWide::Update(const float delta_time)
{
  if(!m_Active) return;
}

void RaidWide::UpdateAnimation()
{
  if(!m_Active) return;
 
  Entity::UpdateAnimation();
}
