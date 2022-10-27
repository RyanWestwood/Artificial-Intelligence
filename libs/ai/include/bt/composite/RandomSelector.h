#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RandomSelector : public CompositeNode {
		public:
			RandomSelector() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI