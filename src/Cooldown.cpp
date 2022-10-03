#include "Cooldown.h"

#define TILE_SIZE 64
#define FPO 8	// Foreground Position Offset
#define FSO 16	// Foreground Size Offset
#define TXO 6	// Text X Position Offset
#define TYO 4	// Text Y Position Offset

void Cooldown::Start()
{
	m_IsCountingDown = true;
}

void Cooldown::Initialize(SDL_Point position, float timer)
{
	m_IsCountingDown = false;

	m_Background.Initialize("ui_backdrop.png");
	m_Background.m_Destination = { position.x,position.y,TILE_SIZE,TILE_SIZE };

	m_Foreground.Initialize("ui_foredrop.png");
	m_Foreground.m_Destination = { position.x + FPO,position.y + FPO,TILE_SIZE - FSO,TILE_SIZE - FSO };

	m_Text.Initalize("font.ttf", "1");
	m_Text.m_Dimensions.x = position.x - TXO + (TILE_SIZE - m_Text.m_Dimensions.w / 2) / 2;
	m_Text.m_Dimensions.y = position.y - TYO + (TILE_SIZE - m_Text.m_Dimensions.h / 2) / 2;
	
	m_Distance = 100.f;
	m_Timer = timer;
	m_Cooldown = timer;
}

void Cooldown::Update(float delta_time)
{
	if (m_IsCountingDown) {
		m_Timer -= delta_time;
		m_Foreground.m_Destination.h = 48 * ((m_Timer / m_Cooldown));

		m_Message = std::to_string(m_Timer);
		m_Message.resize(3);
		m_Text.UpdateMessage(m_Message.c_str());
		m_Text.m_Dimensions.x = m_Background.m_Destination.x - TXO + (TILE_SIZE - m_Text.m_Dimensions.w / 2) / 2;
		m_Text.m_Dimensions.y = m_Background.m_Destination.y - TYO + (TILE_SIZE - m_Text.m_Dimensions.h / 2) / 2;

		if (m_Timer <= 0.f) {
#ifdef LOGGING
			std::cout << "Cooldown!\n";
#endif // LOGGING
			m_Timer = m_Cooldown;
			m_IsCountingDown = false;
		}
	}
}

void Cooldown::Draw()
{
	m_Background.Draw();
	if (m_IsCountingDown) {
		m_Foreground.Draw();
		m_Text.Draw();
	}
}