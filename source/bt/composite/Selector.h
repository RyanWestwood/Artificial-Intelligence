#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {
		
		class Selector : public CompositeNode {
		public:
			Selector() {}
			Status Update(const float delta_time);
		};
	} // namespace BT
} // namespace AI