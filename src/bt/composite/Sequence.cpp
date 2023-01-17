#include "Sequence.h"

namespace ai {
	namespace bt {

		Status Sequence::Update(const float delta_time) {
			for (auto child : m_Children) {
				if (child.Update(delta_time) == Status::Failure) {
					return Status::Failure;
				}
			}
			return Status::Success;
		}
	} // namespace BT
} // namespace AI