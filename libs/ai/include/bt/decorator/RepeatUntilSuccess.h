#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RepeatUntilSuccess : public Decorator {
		public:
			RepeatUntilSuccess() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI