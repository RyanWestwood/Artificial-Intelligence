#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Sound.h"
#include "Font.h"
#include "Nodemap.h"

#include "../Tilemap.h"
#include "../Player.h"
#include "../Enemy.h"

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

private:

public:
	Text text;
	Music music;
	SoundEffect sfx;
	Tilemap tilemap;
	Player player;
	bool m_IsPaused;
	Enemy m_Enemy;
	NodeGrid m_NodeGrid;

private:

};