#include "RepeatN.h"

namespace ai {
	namespace bt {

		Status RepeatN::Update(const float delta_time) {
			int index = 0;
			do {
				Status result = m_Child.Update(delta_time);
				if (result == Status::Failure) {
					return Status::Failure;
				}
				index++;
			} while (index < m_Repitions);
			return Status::Success;
		}
	} // namespace BT
} // namespace AI