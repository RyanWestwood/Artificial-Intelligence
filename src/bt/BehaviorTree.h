#pragma once
#include "Node.h"

namespace ai {
	namespace bt {

		class BehaviourTree {
			BehaviourTree() {}

			void Update() { root.Update(); }
			void Pause() {}
			void Stop() {}

		private:
			Node root;
		};
	} // namespace BT
} // namespace AI
