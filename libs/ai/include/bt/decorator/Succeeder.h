#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Succeeder : public Decorator {
		public:
			Succeeder() {}

			Status Update() {
				m_Child.Update();
				return Status::Success;
			}
		};
	} // namespace BT
} // namespace AI