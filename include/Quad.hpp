#include "Position.hpp"
#include "Point.hpp"
#include "MultiShape.hpp"

namespace shapegame {
	class Quad : public MultiShape {
		public:
		using MultiShape::MultiShape;
		Quad(Position p1, Point p2, Point p3, Point p4, Color color);
		virtual ~Quad() = default;
	};
}
