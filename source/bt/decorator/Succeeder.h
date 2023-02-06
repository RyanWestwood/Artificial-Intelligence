#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class Succeeder : public Decorator {
		public:
			Succeeder() {}
			Status Update(const float delta_time);
		};
	} // namespace BT
} // namespace AI