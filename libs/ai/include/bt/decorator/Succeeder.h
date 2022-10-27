#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Succeeder : public Decorator {
		public:
			Succeeder() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI