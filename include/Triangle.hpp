#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "shapegl.hpp"

namespace shapegame {
    class Triangle : public Shape {
        private:
            float _height;
            float _width;
            float _angles[3];
        public:
            Triangle(float height, float width, float angle1, float angle2,
                    Position pos, Color color);

            Triangle(float height, float width, float angle1, float angle2,
                    double x, double y, Color color);

    };
}
