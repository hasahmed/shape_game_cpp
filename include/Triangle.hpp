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
                0.9f,  0.9f, 0.0f,  // top right
                -0.9f, -0.9f, 0.0f,  // bottom left
                0.9f, -0.9f, 0.0f  // bottom right
            };
            int _numVerts = 9;
            GLuint _vao, _vbo;
            int _vertexAttribIndex;
            Triangle(int height, int width, double x, double y, Color color);
            Triangle(int height, int width, Position pos, Color color);
    };
}
