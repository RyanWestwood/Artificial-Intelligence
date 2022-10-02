#include "Pathfinding.h"
#include <iostream>

namespace AI {
	namespace PATH {

		Node::Node()
		{
			m_Obstacle = false;
			m_Visited = false;
			m_Costs = { 0,0,0 };
			m_Position = { 0,0 };
			m_Neighbours;
			m_Parent;
		}

		NodeMap::NodeMap(int map_width, int map_height)
		{
			m_Map.reserve(map_width * map_height);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					auto a = std::make_shared<Node>();
					a->SetObstacle(false);
					a->SetVisited(false);
					a->SetPosition({ x, y });
					a->SetParent(nullptr);
					a->SetObstacle(false);
					m_Map.push_back(a);
				}
			}

			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (y > 0)
						m_Map[y * map_width + x]->AddNeighbours(m_Map[(y - 1) * map_width + (x)]);
					if (y < map_height - 1)
						m_Map[y * map_width + x]->AddNeighbours(m_Map[(y + 1) * map_width + (x)]);
					if (x > 0)
						m_Map[y * map_width + x]->AddNeighbours(m_Map[(y)*map_width + (x - 1)]);
					if (x < map_width - 1)
						m_Map[y * map_width + x]->AddNeighbours(m_Map[(y)*map_width + (x + 1)]);
				}
			}
		}

		std::vector<NodePtr> NodeMap::GetMap() {
			return m_Map;
		}

		std::shared_ptr<NodeMap> CreateNodeMap(int x, int y)
		{
			return std::make_shared<NodeMap>(x,y);
		}

	} // namespace PATH
} // namespace AI