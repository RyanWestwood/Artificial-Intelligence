#include "Sequence.h"
#include <iostream>

namespace ai {
	namespace bt {

		Status Sequence::Update(const float delta_time) {
			Status result = Status::Error;
			for (auto child : m_Children) {
				result = child.Update(delta_time);
				if (result == Status::Failure) {
					return Status::Failure;
				}
			}
			return result;
		}
	} // namespace BT
} // namespace AI