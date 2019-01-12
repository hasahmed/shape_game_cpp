#pragma once
#include "Scene.hpp"
#include "shapegl.hpp"
namespace shapegame {
    class Drawable {
        friend class Scene;
        protected:
            int _vertexAttribIndex;
            GLuint _vao, _vbo;
            float *_verts;
            int _numVerts;
    };
}