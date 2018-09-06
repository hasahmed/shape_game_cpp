#pragma once
#include "Scene.hpp"
namespace shapegame {
    class Drawable {
        friend class Scene;
        private:
            int _vertexAttribIndex;
            GLuint _vao, _vbo;
            float *_verts;
            int _numVerts;
        protected:
            Drawable();
            Drawable(int numVerts);
            // = 0; is c++ syntax for 'true virtual' meaning the class is
            // abstract and must be derived
            //virtual void draw() = 0;
    };
}

