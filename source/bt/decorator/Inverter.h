#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class Inverter : public Decorator {
		public:
			Inverter() {}
			Status Update(const float delta_time);
		};
	} // namespace BT
} // namespace AI
