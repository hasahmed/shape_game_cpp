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
						int numVerts = 6;
            float verts[6];
            GLRenderObject(Shape &s, GLuint shaderProg);
						GLRenderObject() = default;
    };
}
std::ostream& operator<< (std::ostream& stream, const shapegame::GLRenderObject& rObj);
