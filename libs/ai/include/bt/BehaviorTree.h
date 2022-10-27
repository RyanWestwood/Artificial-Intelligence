#pragma once
#include "../Dll.h"
#include "Node.h"

namespace AI {
	namespace BT {

		class BehaviourTree {
			BehaviourTree() {}

			void Update() { root.Update(); }
			void Pause() {}
			void Stop() {}

		private:
			Node root;
			// root = sequence or selector
		};
	} // namespace BT
} // namespace AI