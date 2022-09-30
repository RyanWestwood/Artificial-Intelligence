#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Sound.h"
#include "Font.h"

#include "../Tilemap.h"
#include "../Player.h"

class Engine {
public:
	bool Initialize();
	void UnInitialize();

	bool IsRunning();
	bool IsPaused();
	void Resume();

	void Input();
	void Draw();
	void Update(double);
	void UpdateAnimation(double*);

private:

public:
	Text text;
	Music music;
	SoundEffect sfx;
	Tilemap tilemap;
	Player player;
	bool m_IsPaused;

private:

};