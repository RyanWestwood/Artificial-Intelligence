#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Inverter : public Decorator {
		public:
			Inverter() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI
