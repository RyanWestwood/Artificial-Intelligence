#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RepeatN : public Decorator {
		public:
			RepeatN(int amount_of_repitions) : m_Repitions(amount_of_repitions){}

			Status Update() {
				for (int i = 0; i < m_Repitions; i++)
				{
					Status result = m_Child.Update();
				}
			}

		private:
			int m_Repitions;
		};
	} // namespace BT
} // namespace AI