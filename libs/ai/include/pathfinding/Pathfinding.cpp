#include "Pathfinding.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

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
					auto node = std::make_shared<Node>();
					node->SetObstacle(false);
					node->SetVisited(false);
					node->SetPosition({ x, y });
					node->SetParent(nullptr);
					node->SetObstacle(false);
					m_Map.push_back(node);
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

		std::shared_ptr<NodeMap> CreateNodeMap(int x, int y)
		{
			return std::make_shared<NodeMap>(x, y);
		}

		void ResetArray(std::vector<NodePtr> nodes) {
			for (int x = 0; x < 48; x++)
			{
				for (int y = 0; y < 27; y++)
				{
					nodes[y * 48 + x]->SetCosts({ FLT_MAX, FLT_MAX, FLT_MAX });
					nodes[y * 48 + x]->SetVisited(false);
					nodes[y * 48 + x]->SetParent(nullptr);
				}
			}
		}

		std::vector<NodePtr> A_Star(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {

			ResetArray(nodes);

			auto Hueristic = [](NodePtr current, NodePtr destination) {
				int xDist = std::max(current->m_Position.x, destination->m_Position.x) - std::min(current->m_Position.x, destination->m_Position.x);
				int yDist = std::max(current->m_Position.y, destination->m_Position.y) - std::min(current->m_Position.y, destination->m_Position.y);
				return static_cast<float>(sqrt((xDist * xDist) + (yDist * yDist)));
			};

			NodePtr currentNode = start_node;
			start_node->m_Costs.m_FromCost = 0.f;
			start_node->m_Costs.m_ToCost = Hueristic(start_node, end_node);
			start_node->m_Costs.m_TotalCost = currentNode->m_Costs.m_FromCost + currentNode->m_Costs.m_ToCost;

			std::vector<NodePtr> nodesToTest;
			nodesToTest.push_back(start_node);

			while (!nodesToTest.empty()) {

				std::sort(begin(nodesToTest), end(nodesToTest), [](NodePtr lhs, NodePtr rhs) {
					return lhs->m_Costs.m_TotalCost < rhs->m_Costs.m_TotalCost;
					});

				while (!nodesToTest.empty() && nodesToTest.front()->IsVisited())
					nodesToTest.erase(begin(nodesToTest));

				if (nodesToTest.empty())
					break;

				currentNode = nodesToTest.front();
				currentNode->SetVisited(true);

				for (NodePtr& nodeNeighbour : currentNode->GetNeighbours()) {
					if (!nodeNeighbour->IsVisited() || !nodeNeighbour->IsObstacle())
						nodesToTest.push_back(nodeNeighbour);

					float gPossibleLowerGoal = currentNode->m_Costs.m_FromCost + Hueristic(currentNode, nodeNeighbour);

					if (gPossibleLowerGoal < nodeNeighbour->m_Costs.m_FromCost) {
						nodeNeighbour->SetParent(currentNode);
						nodeNeighbour->m_Costs.m_FromCost = gPossibleLowerGoal;
						nodeNeighbour->m_Costs.m_ToCost = nodeNeighbour->m_Costs.m_FromCost + Hueristic(currentNode, end_node);
						nodeNeighbour->m_Costs.m_TotalCost = nodeNeighbour->m_Costs.m_FromCost + nodeNeighbour->m_Costs.m_ToCost;
					}
				}
			}

			std::vector<NodePtr> path;
			NodePtr pathNode = end_node;
			while (pathNode->GetParent() != nullptr) {
				path.insert(begin(path), pathNode);
				pathNode = pathNode->m_Parent;
			}
			path.insert(begin(path), pathNode);

			return path;
		}

		std::vector<NodePtr> BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {
			
			ResetArray(nodes);

			auto GoalTest = [](NodePtr current, NodePtr destination) -> bool {
				bool x = current->GetPosition().x == destination->GetPosition().x;
				bool y = current->GetPosition().y == destination->GetPosition().y;
				return x && y;
			};

			std::deque<NodePtr> frontie;
			std::set<NodePtr> explored;
			NodePtr solution_node;

			frontie.push_back(start_node);

			while (!frontie.empty()) {
				NodePtr state = frontie.front();
				frontie.pop_front();
				explored.insert(state);

				if (GoalTest(state, end_node)) {
					solution_node = state;
					break;
				}

				for (NodePtr& neighbour : state->GetNeighbours()) {
					auto it = std::find(frontie.begin(), frontie.end(), neighbour);
					if (!(it != frontie.end())) {
						if (!explored.contains(neighbour)) {
							neighbour->m_Parent = state;
							frontie.push_back(neighbour);
						}
					}
				}
			}

			std::vector<NodePtr> path;
			while (solution_node->GetParent() != nullptr) {
				path.insert(begin(path), solution_node);
				solution_node = solution_node->m_Parent;
			}
			path.insert(begin(path), solution_node);

			return path;
		}

		std::vector<NodePtr> DFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {
			
			ResetArray(nodes);

			auto GoalTest = [](NodePtr current, NodePtr destination) -> bool {
				bool x = current->GetPosition().x == destination->GetPosition().x;
				bool y = current->GetPosition().y == destination->GetPosition().y;
				return x && y;
			};

			std::deque<NodePtr> frontie;
			std::set<NodePtr> explored;
			NodePtr solution_node;

			frontie.push_back(start_node);

			while (!frontie.empty()) {
				NodePtr state = frontie.back();
				frontie.pop_back();
				explored.insert(state);

				if (GoalTest(state, end_node)) {
					solution_node = state;
					break;
				}

				for (NodePtr& neighbour : state->GetNeighbours()) {
					auto it = std::find(frontie.begin(), frontie.end(), neighbour);
					if (!(it != frontie.end())) {
						if (!explored.contains(neighbour)) {
							neighbour->m_Parent = state;
							frontie.push_back(neighbour);
						}
					}
				}
			}

			std::vector<NodePtr> path;
			while (solution_node->GetParent() != nullptr) {
				path.insert(begin(path), solution_node);
				solution_node = solution_node->m_Parent;
			}
			path.insert(begin(path), solution_node);

			return path;
		}
	} // namespace PATH
} // namespace AI