#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class RandomSelector : public CompositeNode {
		public:
			RandomSelector() {}
			Status Update(const float delta_time);
		};
	} // namespace BT
} // namespace AI