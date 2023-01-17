#include "RandomSequence.h"
#include <algorithm>
#include <random>

namespace ai {
	namespace bt {

		Status RandomSequence::Update(const float delta_time) {
			auto rng = std::default_random_engine{};
			std::shuffle(std::begin(m_Children), std::end(m_Children), rng);
			for (auto child : m_Children) {
				if (child.Update(delta_time) == Status::Failure) {
					return Status::Failure;
				}
			}
			return Status::Success;
		}
	} // namespace BT
} // namespace AI