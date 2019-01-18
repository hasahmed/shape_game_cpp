#pragma once
#include <vector>
#include "shapegl.hpp"
#include "Shape.hpp"

namespace shapegame {
    class GLRenderObject {
        public:
            int vertexAttribIndex;
            GLuint vao;
            GLuint vbo;
						GLuint shaderProg;
            std::vector<float> verts;
            GLRenderObject(Shape &s, GLuint shaderProg);
            GLRenderObject() = default;
    };
}
