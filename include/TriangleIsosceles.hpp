#include "Triangle.hpp"
#include "Point.hpp"

namespace shapegame {
	class TriangleIsosceles : public Triangle {
		public:
		TriangleIsosceles(float width=100, float height=100, Point pos=Point(), Color color=Color::BLACK);
	};
}