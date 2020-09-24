#pragma once
#include "Rectangle.hpp"
#include "Color.hpp"

namespace shapegame {
    class Square : public Rectangle {
			public:
				Square(Point position, float size);
				Square(Point position, float size, Color color);
    };
}
