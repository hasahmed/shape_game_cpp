#pragma once
#include "shapegl.hpp"

namespace shapegame {
    struct GLRenderObject {
        public:
            int _vertexAttribIndex;
            GLuint _vao, _vbo;
            float *_verts;
            int _numVerts;
    };
}
