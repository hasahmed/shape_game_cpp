#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "shapegl.hpp"

namespace shapegame {
    class Triangle : public Shape {
        private:
            int _height;
            int _width;
            Position _pos;
            float _verts[9] = {
                //right side triangle
                0.5f,  0.5f, 0.0f,  // top right
                -0.5f, -0.5f, 0.0f,  // bottom left
                0.5f, -0.5f, 0.0f  // bottom right
            };
        public:
            Triangle(int height, int width, double x, double y, Color color);
            Triangle(int height, int width, Position pos, Color color);
    };
}
