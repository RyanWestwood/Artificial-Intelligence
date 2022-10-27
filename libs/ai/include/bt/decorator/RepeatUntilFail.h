#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RepeatUntilFail : public Decorator {
		public:
			RepeatUntilFail() {}

			Status Update() {
				while (true) {
					Status result = m_Child.Update();

					if (result == Status::Failure) {
						return Status::Success;
					}
				}
			}
		};
	} // namespace BT
} // namespace AI