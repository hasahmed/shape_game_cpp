#include "Triangle.hpp"
#include "Position.hpp"
#include "Point.hpp"

namespace shapegame {
	class TriangleIsosceles : public Triangle {
		public:
		TriangleIsosceles(float width, float height, Position pos, Color color);
	};
}
