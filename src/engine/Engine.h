#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Sound.h"
#include "../Tilemap.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Boss.h"

class Engine {
public:
	bool Initialize();
	void UnInitialize();

	bool IsRunning();
	bool IsPaused();
	void Resume();

	void Input();
	void Draw();
	void Update(const float&);
	void UpdateAnimation(float*);
	void UpdateAi(float*);

public:
	Music m_Music;
	SoundEffect m_SoundEffect;
	Tilemap m_Tilemap;
	Player m_Player;
	bool m_IsPaused;
	Enemy m_Enemy;
	Boss m_Boss;
};