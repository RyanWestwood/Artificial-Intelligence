#include "Cooldown.h"

void Cooldown::Initialize(SDL_Point position)
{
	m_Background.Initialize("ui_backdrop.png");
	m_Background.m_Destination = { position.x,position.y,64,64 };

	m_Foreground.Initialize("ui_foredrop.png");
	m_Foreground.m_Destination = { position.x + 8,position.y + 8,64 - 16,64 - 16 };

	m_Text.Initalize("font.ttf", "1");
	m_Text.m_Dimensions.x = position.x - 2 + (64 - m_Text.m_Dimensions.w / 2) / 2;
	m_Text.m_Dimensions.y = position.y - 4 + (64 - m_Text.m_Dimensions.h / 2) / 2;
	
	m_Distance = 100.f;
	m_Timer = 0.f;
	m_Cooldown = 2.f;
}

void Cooldown::Update(float delta_time)
{
	m_Timer += delta_time;

	if (m_Timer >= m_Cooldown) {
#ifdef LOGGING
		std::cout << "Cooldown!\n";
#endif
		m_Timer = 0.f;
	}
}

void Cooldown::Draw()
{
	m_Background.Draw();
	m_Foreground.Draw();
	m_Text.Draw();
}