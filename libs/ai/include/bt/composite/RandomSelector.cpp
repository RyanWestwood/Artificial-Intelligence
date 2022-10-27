#include "RandomSelector.h"
#include <algorithm>
#include <random>

namespace AI {
	namespace BT {

		Status RandomSelector::Update() {
			auto rng = std::default_random_engine{};
			std::shuffle(std::begin(m_Children), std::end(m_Children), rng);
			for (auto child : m_Children) {
				if (child.Update() == Status::Success) {
					return Status::Success;
				}
			}
			return Status::Failure;
		}
	} // namespace BT
} // namespace AI