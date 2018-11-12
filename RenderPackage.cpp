#include <memory>
#include <iostream>
#include "shapegame"

shapegame::RenderPackage::RenderPackage(const Shape *shape,
        GLRenderObject *glRenderObject) {

    this->shape = std::make_unique<Shape>(*shape);
    this->glRenderObject = std::make_unique<GLRenderObject>(*glRenderObject);
}