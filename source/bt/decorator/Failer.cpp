#include "Failer.h"

namespace ai {
	namespace bt {

		Status Failer::Update(const float delta_time) {
			m_Child.Update(delta_time);
			return Status::Failure;
		}
	} // namespace BT
} // namespace AI