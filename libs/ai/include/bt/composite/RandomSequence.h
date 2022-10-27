#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RandomSequence : public CompositeNode {
		public:
			RandomSequence() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI