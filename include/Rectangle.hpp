#pragma once

#include "Triangle.hpp"
#include "MultiShape.hpp"

namespace shapegame {
	class Rectangle : public MultiShape{
		public:
			Rectangle(float width, float height, Position pos, Color color);
			// Rectangle();
	};
}
