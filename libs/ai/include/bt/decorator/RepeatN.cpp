#include "RepeatN.h"

namespace AI {
	namespace BT {

		Status RepeatN::Update() {
			int index = 0;
			do {
				Status result = m_Child.Update();
				if (result == Status::Failure) {
					return Status::Failure;
				}
				index++;
			} while (index < m_Repitions);
			return Status::Success;
		}
	} // namespace BT
} // namespace AI