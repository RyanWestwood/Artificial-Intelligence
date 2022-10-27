#pragma once
#include <algorithm>
#include <random>
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Sequence : public CompositeNode {
		public:
			Sequence() {}

			Status Update() {
				auto rng = std::default_random_engine{};
				std::shuffle(std::begin(m_Children), std::end(m_Children), rng);
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