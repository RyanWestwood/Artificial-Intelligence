#include "Healthbar.h"

HealthBar::HealthBar()
{
  m_BarWidth = 0;
  m_Border   = 0;
}

void HealthBar::Initialize(SDL_Rect position, int border)
{
  m_Border = border;
  m_Background.Initialize({32, 32, 32, 255}, {32, 32});
  m_Background.m_Destination = position;
  m_Foreground.Initialize({255, 0, 0, 255}, {32, 32});
  m_Foreground.m_Destination = {position.x + m_Border,
                                position.y + m_Border,
                                position.w - (2 * m_Border),
                                position.h - (2 * m_Border)};
  m_BarWidth                 = m_Background.m_Destination.w - (2 * m_Border);
}

void HealthBar::Draw()
{
  m_Background.Draw();
  m_Foreground.Draw();
}

void HealthBar::ChangeHealth(int health_percentage)
{
  m_Foreground.m_Destination.w = (m_BarWidth / 100.f) * health_percentage;
}