#include "Sequence.h"

namespace AI {
	namespace BT {

		Status Sequence::Update() {
			for (auto child : m_Children) {
				if (child.Update() == Status::Failure) {
					return Status::Failure;
				}
			}
			return Status::Success;
		}
	} // namespace BT
} // namespace AI