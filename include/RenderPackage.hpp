#pragma once
#include <memory>
#include <iostream>
#include "Shape.hpp"
#include "GLRenderObject.hpp"
namespace shapegame {
    class RenderPackage {
        public:
            std::unique_ptr<Shape> shape;
            std::unique_ptr<GLRenderObject> glRenderObject;
            RenderPackage(const Shape *shape, GLRenderObject *glRenderObject);
            // friend std::ostream & operator<<( std::ostream &os, const std::unique_ptr<RenderPackage>& rp);
            bool updateDirty();
    };
}