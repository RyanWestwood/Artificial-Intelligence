#pragma once
#include "../math/Vector2.h"

namespace AI {
	namespace PATH {
		
		class ILine {
		public:
			virtual bool GetSide(Vector2 point) = 0;
			virtual bool HasCrossedLine(Vector2 point) = 0;
		};

		class Line : public ILine{
		public:
			Line(Vector2 point_on_line, Vector2 point_perpendiculat_to_line);
			bool GetSide(Vector2 point);
			bool HasCrossedLine(Vector2 point);

		private:
			const float m_VerticalLineGradient = 1e5f;
			bool m_ApproachSide;
			float m_Gradient;
			float m_InterceptY;
			float m_PerpendiculatGradient;		
			Vector2 m_Point1;
			Vector2 m_Point2;
		};
	} // namespace PATH
} // namespace AI