#pragma once
#include "Texture.h"
#include "Renderer.h"
#include "Sound.h"
#include "Font.h"

class Engine {
public:
	bool Initialize();
	void Unintialize();

	bool IsRunning();
	bool IsPaused();
	void Resume();

	void Input();
	void Draw();
	void Update(double);

private:

public:
	Text text;
	Sprite sprite;
	Music music;
	SoundEffect sfx;
private:

};