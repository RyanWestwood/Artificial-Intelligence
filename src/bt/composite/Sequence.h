#pragma once
#include "../Node.h"

namespace ai {
	namespace bt {

		class Sequence : public CompositeNode {
		public:
			Sequence() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI