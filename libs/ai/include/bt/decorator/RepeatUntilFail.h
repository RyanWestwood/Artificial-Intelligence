#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RepeatUntilFail : public Decorator {
		public:
			RepeatUntilFail() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI