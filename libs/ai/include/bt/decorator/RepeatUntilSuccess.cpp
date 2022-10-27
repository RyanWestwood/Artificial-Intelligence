#include "RepeatUntilSuccess.h"

namespace AI {
	namespace BT {

		Status RepeatUntilSuccess::Update() {
			while (true) {
				Status result = m_Child.Update();
				if (result == Status::Success) {
					return Status::Success;
				}
			}
		}
	} // namespace BT
} // namespace AI