#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class Sequence : public CompositeNode {
		public:
			Sequence() {}
			Status Update(const float delta_time);
		};
	} // namespace BT
} // namespace AI