#pragma once
#include "Shape.hpp"
#include "Color.hpp"

namespace shapegame {
    class Square : Shape {
        private:
        float _verts[18] = {
            //right side triangle
            0.5f,  0.5f, 0.0f,  // top right
            -0.5f, -0.5f, 0.0f,  // bottom left
            0.5f, -0.5f, 0.0f,  // bottom right

            0.5f,  0.5f, 0.0f,  // top right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        };
    };
}
