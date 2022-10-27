#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {
		
		class Selector : public CompositeNode {
		public:
			Selector() {}

			Status Update() {
				for (auto child : m_Children) {
					if (child.Update() == Status::Success) {
						return Status::Success;
					}
				}
				return Status::Failure;
			}
		};
	} // namespace BT
} // namespace AI