#include "Triangle.hpp"
#include "Position.hpp"
#include "Point.hpp"

namespace shapegame {
	class TriangleIsosceles : public Triangle {
		public:
		TriangleIsosceles(float width=100, float height=100, Position pos=Position(), Color color=Color::BLACK);
	};
}