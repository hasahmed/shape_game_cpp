#include <memory>
#include <iostream>
#include "shapegame.hpp"

using namespace shapegame;

RenderPackage::RenderPackage(Shape &shape,
        GLRenderObject &glRenderObject): shape(shape) {
    this->glRenderObject = std::make_unique<GLRenderObject>(glRenderObject);
}
RenderPackage::RenderPackage(const RenderPackage &rPack):
	shape(rPack.shape) {
		this->glRenderObject = std::make_unique<GLRenderObject>(*rPack.glRenderObject.get());
	}

bool RenderPackage::updateDirty() {
    if (this->shape.isDirty()){
        VertexGenerator::instance()->generate(this->shape, this->glRenderObject->verts);
		this->shape.setDirty(false);
        return true;
    }
    return false;
}

RenderPackage::~RenderPackage(){
	#if PRINT_DESTRUCTION
	std::cout << "RenderPackage Killed" << std::endl;
	#endif
}