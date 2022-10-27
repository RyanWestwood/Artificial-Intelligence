#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Inverter : public Decorator {
		public:
			Inverter() {}

			Status Update() {
				Status result = m_Child.Update();
				if (result == Status::Success) {
					return Status::Failure;
				}
				else if (result == Status::Failure) {
					return Status::Success;
				}
				return result;
			}
		};
	} // namespace BT
} // namespace AI
