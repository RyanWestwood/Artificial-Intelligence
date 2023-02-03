#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class Failer : public Decorator {
		public:
			Failer() {}
			Status Update(const float delta_time);
		};
	} // namespace BT
} // namespace AI
