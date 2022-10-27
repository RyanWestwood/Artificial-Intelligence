#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {
		
		class Selector : public CompositeNode {
		public:
			Selector() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI