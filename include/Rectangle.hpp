#pragma once

#include "Triangle.hpp"
#include "MultiShape.hpp"

namespace shapegame {
	class Rectangle : public MultiShape {
		public:
			virtual ~Rectangle();
			Rectangle(float width, float height, Point pos, Color color);
	};
}
