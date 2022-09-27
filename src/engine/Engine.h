#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Sound.h"

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

private:

};