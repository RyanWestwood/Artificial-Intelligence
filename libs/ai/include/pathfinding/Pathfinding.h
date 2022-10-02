#pragma once
#include "../Dll.h"
#include <vector>
#include <memory>

namespace AI {
	namespace PATH{

		class Node;
		typedef std::shared_ptr<Node> NodePtr;

		struct Vector {
			int x, y;
		};

		struct Costs {
			float g, h, f;
		};

		class INode {
		public:
			virtual bool IsObstacle() = 0;
			virtual bool IsVisited() = 0;
			virtual Vector GetPosition() = 0;
			virtual Costs GetCosts() = 0;
			virtual std::vector<NodePtr> GetNeighbours() = 0;
			virtual NodePtr GetParent() = 0;

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
			std::vector<NodePtr> GetNeighbours() { return m_Neighbours; }
			NodePtr GetParent() { return m_Parent; }

			void SetObstacle(bool obstacle) { m_Obstacle = obstacle; }
			void SetVisited(bool visited) { m_Visited = visited; }
			void SetPosition(Vector position) { m_Position = position; }
			void SetCosts(Costs costs) { m_Costs = costs; }
			void SetParent(NodePtr parent) { m_Parent = parent; }
			void AddNeighbours(NodePtr neighbours) { m_Neighbours.push_back(neighbours); }
		private:
			bool m_Obstacle;
			bool m_Visited;
			Costs m_Costs;
			Vector m_Position;
			std::vector<NodePtr> m_Neighbours;
			NodePtr m_Parent;
		};
		
		class INodeMap {
		public:
			virtual std::vector<NodePtr> GetMap() = 0;
		};

		class NodeMap {
		public:
			NodeMap(int, int);
			std::vector<NodePtr> GetMap();

		public:
			std::vector<NodePtr> m_Map;
		};

		extern "C++" AI_API std::shared_ptr<NodeMap> CreateNodeMap(int,int);
	} // namespace PATH
} // namespace AI