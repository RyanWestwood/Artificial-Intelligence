#include "Pathfinding.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
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

		std::vector<NodePtr> CreateNodeMap(int map_width, int map_height)
		{
			std::vector<NodePtr> map{};
			map.reserve(map_width * map_height);
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
					map.push_back(node);
				}
			}

			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (y > 0)
						map[y * map_width + x]->AddNeighbours(map[(y - 1) * map_width + (x)]);
					if (y < map_height - 1)
						map[y * map_width + x]->AddNeighbours(map[(y + 1) * map_width + (x)]);
					if (x > 0)
						map[y * map_width + x]->AddNeighbours(map[(y)*map_width + (x - 1)]);
					if (x < map_width - 1)
						map[y * map_width + x]->AddNeighbours(map[(y)*map_width + (x + 1)]);
				}
			}
			return map;
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

		std::vector<Vector> SimplifyPath(std::vector<Vector> path){
			std::vector<Vector> way_points{};
			Vector old_direction{ 0,0 };

			for (int i = 1; i < path.size(); i++)
			{
				Vector new_direction = { path.at(i - 1).x - path.at(i).x, path.at(i - 1).y - path.at(i).y, };
				if(new_direction != old_direction){ 
					way_points.push_back(path.at(i));
				}
				old_direction = new_direction;
			}
			return way_points;
		}

		std::vector<Vector> GetPath(NodePtr solution_node){
			if (!solution_node) return {};
			std::vector<Vector> path;
			while (solution_node->GetParent() != nullptr) {
				path.push_back(solution_node->GetPosition());
				solution_node = solution_node->GetParent();
			}
			path.push_back(solution_node->GetPosition());
			std::vector<Vector> simplified_path = SimplifyPath(path);
			std::reverse(std::begin(simplified_path), std::end(simplified_path));
			return simplified_path;
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
					if (!(it != frontier.end()) && !neighbour->IsObstacle()) {
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

		std::vector<Vector> Greedy_BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {

			ResetArray(nodes);

			struct compare {
				bool operator() (const NodePtr& lhs, const NodePtr& rhs) const {
					if (lhs->m_Costs.m_TotalCost == rhs->m_Costs.m_TotalCost) {
						return lhs->m_Costs.m_FromCost > rhs->m_Costs.m_FromCost;
					}
					return lhs->m_Costs.m_TotalCost > rhs->m_Costs.m_TotalCost;
				}
			};

			start_node->m_Costs.m_FromCost = 0.f;
			start_node->m_Costs.m_ToCost = 0;
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
					if (!(it != frontier.end()) && !neighbour->IsObstacle()) {
						float gPossibleLowerGoal = current_node->m_Costs.m_FromCost;
						if (gPossibleLowerGoal < neighbour->m_Costs.m_FromCost) {
							neighbour->SetParent(current_node);
							neighbour->m_Costs.m_FromCost = current_node->m_Costs.m_FromCost + 1;
							neighbour->m_Costs.m_ToCost = 0;
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
					if (!(it != frontier.end()) && !neighbour->IsObstacle()) {
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
					if (!(it != frontier.end()) && !neighbour->IsObstacle()) {
						if (!explored.contains(neighbour)) {
							neighbour->SetParent(current_node);
							frontier.push_back(neighbour);
						}
					}
				}
			}
			return GetPath(solution_node);
		}

		std::vector<Vector> DLS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node) {

			ResetArray(nodes);

			std::deque<NodePtr> frontier; // use back to imitate stack
			std::set<NodePtr> explored;
			NodePtr solution_node;

			frontier.push_back(start_node);

			int depth_limit = 3;
			int current_depth = 0;
			while (!frontier.empty()) {
				if (current_depth < depth_limit) {
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
						if (!(it != frontier.end()) && !neighbour->IsObstacle()) {
							if (!explored.contains(neighbour)) {
								neighbour->SetParent(current_node);
								frontier.push_back(neighbour);
							}
						}
					}
					current_depth++;
				}else{
					current_depth--;
					//break;// Error is here quits while as soon as depth_limit is reached 
				}
			}
			return GetPath(solution_node);
		}

		DLS_Data DLS(NodePtr start_node, NodePtr end_node, int depth, std::set<NodePtr>& explored){
			if(depth == 0){
				if (GoalTest(start_node, end_node)) {
					return { start_node, true };
				}else{
					return { nullptr, true };
				}
			}else if(depth > 0){
				bool any_remaining = false;
				explored.insert(start_node);
				for(NodePtr child : start_node->GetNeighbours()){
					if (!explored.contains(child)) {
						child->SetParent(start_node);
						DLS_Data res = DLS(child, end_node, depth - 1, explored);
						if (res.found) {
							return { res.found, true };
						}
						if (res.remaining) {
							any_remaining = true;
						}
					}
				}
				return { nullptr, any_remaining };
			}
		}


		std::vector<Vector> DLS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, int depth){
			ResetArray(nodes);

			std::set<NodePtr> explored{};
			DLS_Data res = DLS(start_node, end_node, depth, explored);
			if(res.found){
				return GetPath(res.found);
			}
			return {};
		}

		std::vector<Vector> IDDFS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, int depth_limit) {
			for (int depth = 0; depth < depth_limit; depth += 5)
			{
				auto a = DLS_Caller(nodes, start_node, end_node, depth);
				if(!a.empty()){
					return a;
				}
			}
			return {};
		}

	} // namespace PATH
} // namespace AI