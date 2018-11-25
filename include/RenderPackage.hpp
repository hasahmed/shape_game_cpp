#pragma once
#include <memory>
#include <iostream>
#include "Shape.hpp"
#include "GLRenderObject.hpp"
namespace shapegame {
    class RenderPackage {
        public:
            Shape* shape; // Scene owns this Shape object
            std::unique_ptr<GLRenderObject> glRenderObject;
            RenderPackage(Shape *shape, GLRenderObject *glRenderObject);
            bool updateDirty();
    };
}
