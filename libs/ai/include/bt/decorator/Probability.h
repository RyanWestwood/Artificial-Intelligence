#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Probability : public Decorator {
		public:
			Probability(int probability) : m_Probability(probability) {}
			Status Update();

		private:
			int m_Probability;
		};
	} // namespace BT
} // namespace AI