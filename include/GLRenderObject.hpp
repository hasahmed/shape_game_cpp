#pragma once
#include <vector>
#include "shapegl.hpp"

namespace shapegame {
    struct GLRenderObject {
        public:
            int vertexAttribIndex;
            GLuint vao;
            GLuint vbo;
            std::vector<float> verts;
            ~GLRenderObject(){
                // std::cout << "deleted: GlRenderObject" << std::endl;
            }
    };
}
