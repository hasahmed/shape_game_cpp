#pragma once
#include "Shape.hpp"
namespace shapegame {
    class Rectangle : public Shape {
        public:
            Rectangle(float height, float width, Position pos, Color color);
    };
}
