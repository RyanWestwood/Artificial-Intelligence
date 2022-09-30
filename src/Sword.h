#pragma once
#include "engine/Texture.h"

class Sword{
public:
	Sword() {};

	void Initialize(const char* filename);

public:
	Sprite m_Sprite;
};