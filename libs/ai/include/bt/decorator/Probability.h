#pragma once
#include <random>
#include "../../Dll.h"
#include "../Node.h"

namespace AI {
	namespace BT {

		class Probability : public Decorator {
		public:
			Probability(int probability) : m_Probability(probability) {}

			Status Update() {
				std::random_device dev;
				std::mt19937 rng(dev());
				std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 99);

				if (distribution(rng) < m_Probability) {
					return Status::Success;
				}
				return Status::Failure;
			}

		private:
			int m_Probability;
		};
	} // namespace BT
} // namespace AI