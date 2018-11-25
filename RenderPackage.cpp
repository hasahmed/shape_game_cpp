#include <memory>
#include <iostream>
#include "shapegame"

shapegame::RenderPackage::RenderPackage(const Shape *shape,
        GLRenderObject *glRenderObject): shape(const_cast<Shape*>(shape)) {

    // this->shape = std::unique_ptr<Shape>(const_cast<Shape*>(shape));
    this->glRenderObject = std::make_unique<GLRenderObject>(*glRenderObject);
}
bool shapegame::RenderPackage::updateDirty(){
    if (this->shape->_dirty){
        // super waste. Don't throw away verticies, move them instead.
        this->glRenderObject->verts = VertexGenerator::instance()->generate(*(this->shape));
        this->shape->_dirty = false;
        return true;
    }
    return false;
}