#pragma once
#include "../engine/Font.h"
#include "../engine/Texture.h"

class AbilityBar
{
public:
  AbilityBar();
  void Initialize(SDL_Rect position, int border, const char* ability_name);

  void Draw();
  void ChangeProgress(int ability_percentage);
  void ChangeName();

private:
  Sprite m_Foreground;
  Sprite m_Background;
  int    m_BarWidth;
  int    m_Border;
  Text   m_Name;
};