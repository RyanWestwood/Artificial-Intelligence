#pragma once
#include <memory>
#include <vector>
#include "../Dll.h"
#include "../math/Vector2.h"

namespace AI {
	namespace PATH{

		class Node;
		typedef std::shared_ptr<Node> NodePtr;

		struct Costs {
			float m_FromCost, m_ToCost, m_TotalCost;
		};

		class INode {
		public:
			virtual bool IsObstacle() = 0;
			virtual bool IsVisited() = 0;
			virtual Vector2 GetPosition() = 0;
			virtual Costs GetCosts() = 0;
			virtual NodePtr GetParent() = 0;
			virtual std::vector<NodePtr> GetNeighbours() = 0;

			virtual void SetObstacle(bool obstacle) = 0;
			virtual void SetVisited(bool visited) = 0;
			virtual void SetPosition(Vector2 position) = 0;
			virtual void SetCosts(Costs costs) = 0;
			virtual void SetParent(NodePtr parent) = 0;
			virtual void AddNeighbours(NodePtr neighbours) = 0;
		};

		class Node : public INode{
		public:
			Node();
			bool IsObstacle() { return m_Obstacle; }
			bool IsVisited() { return m_Visited; }
			Vector2 GetPosition() { return m_Position; }
			Costs GetCosts() { return m_Costs; }
			NodePtr GetParent() { return m_Parent; }
			std::vector<NodePtr> GetNeighbours() { return m_Neighbours; }

			void SetObstacle(bool obstacle) { m_Obstacle = obstacle; }
			void SetVisited(bool visited) { m_Visited = visited; }
			void SetPosition(Vector2 position) { m_Position = position; }
			void SetCosts(Costs costs) { m_Costs = costs; }
			void SetParent(NodePtr parent) { m_Parent = parent; }
			void AddNeighbours(NodePtr neighbours) { m_Neighbours.push_back(neighbours); }
		public:
			Costs m_Costs;
		private:
			Vector2 m_Position;
			bool m_Visited;
			NodePtr m_Parent;
			bool m_Obstacle;
			std::vector<NodePtr> m_Neighbours;
		};

		extern "C++" AI_API std::vector<NodePtr> CreateNodeMap(int, int);
		extern "C++" AI_API std::vector<Vector2> A_Star(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector2> BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector2> Greedy_BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector2> DFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);
		extern "C++" AI_API std::vector<Vector2> DLS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node);

		struct DLS_Data {
			NodePtr found;
			bool remaining;
		};
		extern "C++" AI_API std::vector<Vector2> IDDFS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, int depth);
		extern "C++" AI_API std::vector<Vector2> DLS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, int depth);
	} // namespace PATH
} // namespace AI