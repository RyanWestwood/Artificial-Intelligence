#include "Pathfinding.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <math.h>

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

		auto GoalTest = [](NodePtr current, NodePtr destination) -> bool {
			bool x = current->GetPosition().x == destination->GetPosition().x;
			bool y = current->GetPosition().y == destination->GetPosition().y;
			return x && y;
		};

		std::vector<Vector> GetPath(NodePtr solution_node){
			std::vector<Vector> path;
			while (solution_node->GetParent() != nullptr) {
				path.insert(begin(path), solution_node->GetPosition());
				solution_node = solution_node->GetParent();
			}
			path.insert(begin(path), solution_node->GetPosition());
			return path;
		}

		std::vector<Vector> A_Star(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {

			ResetArray(nodes);

			auto Hueristic = [](NodePtr current, NodePtr destination) {
				auto current_pos = current->GetPosition();
				auto destination_pos = destination->GetPosition();
				int xDist = std::max(current_pos.x, destination_pos.x) - std::min(current_pos.x, destination_pos.x);
				int yDist = std::max(current_pos.y, destination_pos.y) - std::min(current_pos.y, destination_pos.y);
				return static_cast<float>((xDist * xDist) + (yDist * yDist));
			};

			struct compare {
				bool operator() (const NodePtr& lhs, const NodePtr& rhs) const {
					if (lhs->m_Costs.m_TotalCost == rhs->m_Costs.m_TotalCost) {
						return lhs->m_Costs.m_FromCost > rhs->m_Costs.m_FromCost;
					}
					return lhs->m_Costs.m_TotalCost > rhs->m_Costs.m_TotalCost;
				}
			};

			start_node->m_Costs.m_FromCost = 0.f;
			start_node->m_Costs.m_ToCost = Hueristic(start_node, end_node);
			start_node->m_Costs.m_TotalCost = start_node->m_Costs.m_FromCost + start_node->m_Costs.m_ToCost;

			std::vector<NodePtr> frontier;
			std::set<NodePtr> explored;
			NodePtr solution_node;

			frontier.push_back(start_node);
			std::make_heap(frontier.begin(), frontier.end(), compare());

			while (!frontier.empty()) {

				std::pop_heap(frontier.begin(), frontier.end(), compare());
				NodePtr current_node = frontier.back();
				if (GoalTest(current_node, end_node)) {
					solution_node = current_node;
					break;
				}
				frontier.pop_back();
				explored.insert(current_node);
				current_node->SetVisited(true);

				for (NodePtr& neighbour : current_node->GetNeighbours()) {
					auto it = std::find(frontier.begin(), frontier.end(), neighbour);
					if (!(it != frontier.end())) {
						float gPossibleLowerGoal = current_node->m_Costs.m_FromCost + Hueristic(neighbour, end_node);
						if (gPossibleLowerGoal < neighbour->m_Costs.m_FromCost) {
							neighbour->SetParent(current_node);
							neighbour->m_Costs.m_FromCost = current_node->m_Costs.m_FromCost + 1;
							neighbour->m_Costs.m_ToCost = Hueristic(neighbour, end_node);
							neighbour->m_Costs.m_TotalCost = neighbour->m_Costs.m_FromCost + neighbour->m_Costs.m_ToCost;
							frontier.push_back(neighbour);
							std::push_heap(frontier.begin(), frontier.end(), compare());
						}
					}
				}
			}
			return GetPath(solution_node);
		}

		std::vector<Vector> BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {
			
			ResetArray(nodes);

			std::deque<NodePtr> frontier;
			std::set<NodePtr> explored;
			NodePtr solution_node;

			frontier.push_back(start_node);

			while (!frontier.empty()) {
				NodePtr current_node = frontier.front();
				if (GoalTest(current_node, end_node)) {
					solution_node = current_node;
					break;
				}
				frontier.pop_front();
				explored.insert(current_node);
				current_node->SetVisited(true);

				for (NodePtr& neighbour : current_node->GetNeighbours()) {
					auto it = std::find(frontier.begin(), frontier.end(), neighbour);
					if (!(it != frontier.end())) {
						if (!explored.contains(neighbour)) {
							neighbour->SetParent(current_node);
							frontier.push_back(neighbour);
						}
					}
				}
			}
			return GetPath(solution_node);
		}

		std::vector<Vector> DFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {
			
			ResetArray(nodes);

			std::deque<NodePtr> frontier;
			std::set<NodePtr> explored;
			NodePtr solution_node;

			frontier.push_back(start_node);

			while (!frontier.empty()) {
				NodePtr current_node = frontier.back();
				if (GoalTest(current_node, end_node)) {
					solution_node = current_node;
					break;
				}
				frontier.pop_back();
				explored.insert(current_node);
				current_node->SetVisited(true);

				for (NodePtr& neighbour : current_node->GetNeighbours()) {
					auto it = std::find(frontier.begin(), frontier.end(), neighbour);
					if (!(it != frontier.end())) {
						if (!explored.contains(neighbour)) {
							neighbour->SetParent(current_node);
							frontier.push_back(neighbour);
						}
					}
				}
			}
			return GetPath(solution_node);
		}
	} // namespace PATH
} // namespace AI