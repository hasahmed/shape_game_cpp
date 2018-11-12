#include <memory>
#include <iostream>
#include "shapegame"

shapegame::RenderPackage::RenderPackage(const Shape *shape,
        GLRenderObject *glRenderObject) {

    this->shape = std::make_unique<Shape>(*shape);
    this->glRenderObject = std::make_unique<GLRenderObject>(*glRenderObject);
}
bool shapegame::RenderPackage::updateDirty(){
    if (this->shape->_dirty){
        this->glRenderObject->verts = VertexGenerator::instance()->generate(*(this->shape));
        this->shape->_dirty = false;
        return true;
    }
    return false;
}