#pragma once
#include "../../Entity.h"
#include "Attack.h"

class RaidWide : IAttack,
                 Entity
{
public:
  RaidWide();

  void Initialize() override;
  void Activate() override;
  void Deactivate() override;

  void Draw() override;
  void Update(const float delta_time) override;
  void UpdateAnimation() override;

private:
  int m_Damage;
};