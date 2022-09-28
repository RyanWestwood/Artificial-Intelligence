#pragma once
#include <vector>
#include "Texture.h"
#include <array>

class Tile {
public:
	Tile(Sprite spritesheet);
	~Tile();

	void Draw();

public:
	Sprite m_Sprite;
};

class Tilemap {
public:
	Tilemap();
	~Tilemap();

	void Initialize();
	void Draw();

public:
	std::array<std::array<int, 48>, 27 > MAP_DATA;
	std::vector<Tile> m_Tiles;
	Sprite m_Spritesheet;
};