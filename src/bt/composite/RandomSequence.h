#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class RandomSequence : public CompositeNode {
		public:
			RandomSequence() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI