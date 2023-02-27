#pragma once

class IAttack
{
public:
  virtual void Initialize() = 0;
  virtual void Activate()   = 0;
  virtual void Deactivate() = 0;

  virtual void Draw()                         = 0;
  virtual void Update(const float delta_time) = 0;
  virtual void UpdateAnimation()              = 0;

protected:
  bool m_Active = false;
};