#pragma once
#include "Vec"

namespace AI {
	namespace PATH {

		class Line{
		public:

			Line(){

			}

			float m_Gradient;
			float m_InterceptY;
			float m_PerpendiculatGradient;			
		};
	} // namespace PATH
} // namespace AI