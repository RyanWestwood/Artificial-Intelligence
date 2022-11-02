#pragma once
#include <SDL.h> 
#include <pathfinding/Algorithms.h>
#include "Globals.h"
#include "Texture.h"
#include "../Entity.h"

namespace PATHING {
	class Node : public Entity {
	public:
		Node() : Entity::Entity() {}

	public:
		SDL_FPoint m_Position;
		SDL_Rect m_Destination;
	#ifdef LOGGING
		void Draw();
		Texture::TextureData m_TextureData;
	#endif // LOGGING
	};

	enum class Algo {
		A_Star = 0,
		BFS,
		DFS,
		GBFS,
		DLS,
		IDDFS
	};

	bool Initialize();
	void UnInitialize();

	std::vector<Vector2> CreatePath(Vector2 start_node, Vector2 end_node, Algo algorithm = Algo::A_Star);
	void Reset();
	void SetObstacle(int x, int y, bool value);
	void UpdateAi();
	std::vector<Node>& GetMap();

#ifdef LOGGING
	void DebugPaths(Globals::Vector& tilemap_dimensions, Globals::Vector tile_size);
	void Input();
	void Draw();
#endif // LOGGING
} // namespace PATHING