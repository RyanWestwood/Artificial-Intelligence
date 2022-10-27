#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Sequence : public CompositeNode {
		public:
			Sequence() {}

			Status Update() {
				for (auto child : m_Children) {
					if (child.Update() == Status::Failure) {
						return Status::Failure;
					}
				}
				return Status::Success;
			}
		};
	} // namespace BT
} // namespace AI