#include "Failer.h"

namespace AI {
	namespace BT {

		Status Failer::Update() {
			m_Child.Update();
			return Status::Failure;
		}
	} // namespace BT
} // namespace AI