#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Failer : public Decorator {
		public:
			Failer() {}

			Status Update() {
				m_Child.Update();
				return Status::Failure;
			}
		};
	} // namespace BT
} // namespace AI
