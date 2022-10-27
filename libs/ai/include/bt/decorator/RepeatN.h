#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class RepeatN : public Decorator {
		public:
			RepeatN(int amount_of_repitions) : m_Repitions(amount_of_repitions){}

			Status Update() {
				int index = 0;
				do {
					result = m_Child.Update();
					if (result == Status::Failure) {
						return Status::Failure;
					}
					index++;
				} while (index < m_Repitions);
				return Status::Success;
			}

		private:
			int m_Repitions;
		};
	} // namespace BT
} // namespace AI