#pragma once
#include "../Dll.h"
#include <vector>
#include <memory>

namespace AI {
	namespace PATH{

		class Node;
		class NodeMap;
		typedef std::shared_ptr<Node> NodePtr;
		typedef std::shared_ptr<NodeMap> NodeMapPtr;

		struct Vector {
			int x, y;
		};

		struct Costs {
			float m_FromCost, m_ToCost, m_TotalCost;
		};

		class INode {
		public:
			virtual bool IsObstacle() = 0;
			virtual bool IsVisited() = 0;
			virtual Vector GetPosition() = 0;
			virtual Costs GetCosts() = 0;
			virtual NodePtr GetParent() = 0;
			virtual std::vector<NodePtr> GetNeighbours() = 0;

			virtual void SetObstacle(bool obstacle) = 0;
			virtual void SetVisited(bool visited) = 0;
			virtual void SetPosition(Vector position) = 0;
			virtual void SetCosts(Costs costs) = 0;
			virtual void SetParent(NodePtr parent) = 0;
			virtual void AddNeighbours(NodePtr neighbours) = 0;
		};

		class Node : public INode{
		public:
			Node();
			bool IsObstacle() { return m_Obstacle; }
			bool IsVisited() { return m_Visited; }
			Vector GetPosition() { return m_Position; }
			Costs GetCosts() { return m_Costs; }
			NodePtr GetParent() { return m_Parent; }
			std::vector<NodePtr> GetNeighbours() { return m_Neighbours; }

			void SetObstacle(bool obstacle) { m_Obstacle = obstacle; }
			void SetVisited(bool visited) { m_Visited = visited; }
			void SetPosition(Vector position) { m_Position = position; }
			void SetCosts(Costs costs) { m_Costs = costs; }
			void SetParent(NodePtr parent) { m_Parent = parent; }
			void AddNeighbours(NodePtr neighbours) { m_Neighbours.push_back(neighbours); }
		public:
			Costs m_Costs;
		private:
			Vector m_Position;
			bool m_Visited;
			NodePtr m_Parent;
			bool m_Obstacle;
			std::vector<NodePtr> m_Neighbours;
		};
		
		class INodeMap {
		public:
			virtual std::vector<NodePtr> GetMap() = 0;
		};

		class NodeMap : public INodeMap{
		public:
			NodeMap(int, int);
			std::vector<NodePtr> GetMap() { return m_Map; }
		private:
			std::vector<NodePtr> m_Map;
		};

		extern "C++" AI_API std::shared_ptr<NodeMap> CreateNodeMap(int, int);
		extern "C++" AI_API std::vector<Vector> A_Star(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector> BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector> Greedy_BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector> DFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector> DLS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
	} // namespace PATH
} // namespace AI