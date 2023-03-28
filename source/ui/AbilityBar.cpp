#include "AbilityBar.h"

AbilityBar::AbilityBar()
{
  m_BarWidth   = 0;
  m_Border     = 0;
  m_CachedName = "";
}

void AbilityBar::Initialize(SDL_Rect position, int border, std::string ability_name)
{
  m_Border = border;
  m_Background.Initialize({32, 32, 32, 255}, {32, 32});
  m_Background.m_Destination = position;
  m_Foreground.Initialize({255, 255, 255, 255}, {32, 32});
  m_Foreground.m_Destination = {position.x + border,
                                position.y + border,
                                position.w - (2 * border),
                                position.h - (2 * border)};
  m_BarWidth                 = m_Background.m_Destination.w - (2 * m_Border);

  m_CachedName = ability_name;
  m_Name.Initalize("font.ttf", ability_name.c_str(), 12);
  m_Name.m_Dimensions.x = position.x - m_Name.m_Dimensions.w;
  m_Name.m_Dimensions.y = position.y;
}

void AbilityBar::Draw()
{
  m_Background.Draw();
  m_Foreground.Draw();
  m_Name.Draw();
}

void AbilityBar::ChangeProgress(int ability_percentage)
{
  m_Foreground.m_Destination.w = (m_BarWidth / 100.f) * ability_percentage;
}

void AbilityBar::ChangeName(std::string name)
{
  if(name == m_CachedName) return;
  m_Name.UpdateMessage(name.c_str());
  m_Name.m_Dimensions.x = m_Background.m_Destination.x - m_Name.m_Dimensions.w;
  m_Name.m_Dimensions.y = m_Background.m_Destination.y;
}