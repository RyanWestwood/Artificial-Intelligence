#pragma once
#include <SDL.h> 
#include <pathfinding/Pathfinding.h>
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
		DFS
	};

	bool Initialize();
	void UnInitialize();

	std::vector<Node>& GetMap();
	std::vector<AI::PATH::Vector> CreatePath(SDL_Point start_node, SDL_Point end_node, Algo algorithm = Algo::A_Star);
	void Reset();
	void SetObstacle(int x, int y, bool value);
	void UpdateAi();

#ifdef LOGGING
	void DebugPaths(Globals::Vector& tilemap_dimensions, Globals::Vector tile_size);
	void Input();
	void Draw();
#endif // LOGGING
} // namespace PATHING