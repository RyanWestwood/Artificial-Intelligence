#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class Failer : public Decorator {
		public:
			Failer() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI
