#pragma once
#include <SDL.h> 
#include <pathfinding/Pathfinding.h>
#include "Texture.h"

class DebugNode {
public:
	DebugNode() {}

	void Draw();

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

#ifdef LOGGING
	void Input();
	void Draw();
#endif // LOGGING

public:
	std::shared_ptr<AI::PATH::NodeMap> m_Map;
	std::vector<AI::PATH::NodePtr> m_Nodes;

#ifdef LOGGING
	bool m_DebugActivate = false;
	Texture::TextureData m_DebugTextureData;
	Texture::TextureData m_DebugTextureExploredData;
	Texture::TextureData m_DebugTextureStartData;
	Texture::TextureData m_DebugTextureEndData;
	std::vector<DebugNode> m_DebugNodes;
#endif // LOGGING
};