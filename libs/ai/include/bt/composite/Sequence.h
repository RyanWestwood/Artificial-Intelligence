#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Sequence : public CompositeNode {
		public:
			Sequence() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI