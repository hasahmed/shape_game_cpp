#include <memory>
#include <iostream>
#include "shapegame"

shapegame::RenderPackage::RenderPackage(Shape *shape,
        GLRenderObject *glRenderObject): shape(shape) {
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