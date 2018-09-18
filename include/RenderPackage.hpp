#pragma once
#include <memory>
#include "Shape.hpp"
#include "GLRenderObject.hpp"
namespace shapegame {
    struct RenderPackage {
        public:
            std::unique_ptr<Shape> shape;
            std::unique_ptr<GLRenderObject> glRenderObject;
            RenderPackage(Shape *shape, GLRenderObject *glRenderObject);
    };
}
