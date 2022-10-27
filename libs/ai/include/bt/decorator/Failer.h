#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Failer : public Decorator {
		public:
			Failer() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI
