#pragma once
#include <SDL.h> 
#include <pathfinding/Pathfinding.h>
#include "Globals.h"
#include "Texture.h"
#include "../Entity.h"

class Node : public Entity {
public:
	Node();
#ifdef LOGGING
	void Draw();
#endif // LOGGING

public:
	SDL_FPoint m_Position;
	Texture::TextureData m_TextureData;
	SDL_Rect m_Destination;
};

class NodeGrid {
public:
	NodeGrid() {}
	~NodeGrid();

	void Initialize();
	void Update();
	void Reset();

	void SetObstacle(int x, int y, bool value);
	std::vector<std::shared_ptr<Node>>& GetNodes() { return m_Nodes; }

	void DebugPaths(Globals::Vector& tilemap_dimensions, int tile_width, int tile_height);

#ifdef LOGGING
	void Input();
	void Draw();
#endif // LOGGING

private:
	std::vector<AI::PATH::NodePtr> m_NodePtrs;
	std::vector<std::shared_ptr<Node>> m_Nodes;

#ifdef LOGGING
	bool m_DebugActivate = false;
	Texture::TextureData m_DebugTextureData;
	Texture::TextureData m_DebugTextureExploredData;
	Texture::TextureData m_DebugTextureStartData;
	Texture::TextureData m_DebugTextureEndData;
	Texture::TextureData m_DebugObstacle;
#endif // LOGGING
};