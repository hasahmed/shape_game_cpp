#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "shapegl.hpp"

namespace shapegame {
    class Triangle {
        private:
            int _height;
            int _width;
            Position _pos;
        public:
            Color color;
            float _verts[9] = {
                // right side triangle
                1.0, 1.0, 0.0f,
                1.0,  -1.0, 0.0f,
                -1.0, -1.0, 0.0f

            };
            int _numVerts = 9;
            GLuint _vao, _vbo;
            int _vertexAttribIndex;
            Triangle(int height, int width, double x, double y, Color color);
            Triangle(int height, int width, Position pos, Color color);
    };
}
