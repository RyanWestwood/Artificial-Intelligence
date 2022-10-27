#include "Succeeder.h"

namespace AI {
	namespace BT {

		Status Succeeder::Update() {
			m_Child.Update();
			return Status::Success;
		}
	} // namespace BT
} // namespace AI

