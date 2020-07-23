#include "Position.hpp"
#include "Point.hpp"
#include "MultiShape.hpp"

namespace shapegame {
	class Circle : public MultiShape {
		public:
		using MultiShape::MultiShape;
		Circle(Position pos, double size, int fidelity, Color color);
		virtual ~Circle() = default;
	};
}
std::ostream& operator<< (std::ostream& stream, const shapegame::GLRenderObject& rObj);
