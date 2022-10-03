#pragma once
#include <array>
#include <vector>
#include "engine/Texture.h"

#ifdef LOGGING
	#include "pathfinding/Pathfinding.h"
#endif // LOGGING

class Tile {
public:
	Tile(Texture::TextureData spritesheet);
	~Tile();

	void Draw();

public:
	Texture::TextureData m_TextureData;
	SDL_Rect m_Destination;
	SDL_Point m_Position;
};

class Tilemap {
public:
	Tilemap();
	~Tilemap();

	void Initialize(const char* filename, int src_tile_size, int dst_tile_size);
	void Draw();

public:
	std::array<std::array<int, 48>, 27 > MAP_DATA;
	std::vector<Tile> m_Tiles;
	Texture::TextureData m_TextureData;	
	SDL_Rect m_Destination;

#ifdef LOGGING
	void Input();
	bool m_DebugActivate = false;
	Texture::TextureData m_DebugTextureData;
	Texture::TextureData m_DebugTextureExploredData;
	std::vector<Tile> m_DebugTiles;
	AI::PATH::NodeMapPtr m_NodeMap;
	std::vector<AI::PATH::NodePtr> m_Nodes;
#endif // LOGGING
};