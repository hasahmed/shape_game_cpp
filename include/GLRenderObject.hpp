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
            float verts[9];
						int numVerts = 9;
            GLRenderObject(Shape &s, GLuint shaderProg);
						GLRenderObject() = default;
    };
}
std::ostream& operator<< (std::ostream& stream, const shapegame::GLRenderObject& rObj);
