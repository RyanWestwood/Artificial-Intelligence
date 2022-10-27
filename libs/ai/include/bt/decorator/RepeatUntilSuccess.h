#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RepeatUntilSuccess : public Decorator {
		public:
			RepeatUntilSuccess() {}

			Status Update() {
				while (true) {
					Status result = m_Child.Update();
					if (result == Status::Success) {
						return Status::Success;
					}
				}
			}
		};
	} // namespace BT
} // namespace AI