#pragma once
#include <iostream>
#include "composite/Sequence.h"

namespace ai {
	namespace bt {

		class BehaviourTree {
		public:
			BehaviourTree() {}
			void Initialize(Sequence root) { m_Root = root; }

			void Update(const float delta_time) { m_Root.Update(delta_time); }
			void Pause() {}
			void Stop() {}

		private:
			Sequence m_Root;
		};
	} // namespace BT
} // namespace AI
