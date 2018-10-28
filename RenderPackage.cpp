#include <memory>
#include <iostream>
#include "shapegame"

shapegame::RenderPackage::RenderPackage(Shape *shape,
        GLRenderObject *glRenderObject) {

    this->shape = std::make_unique<Shape>(*shape);
    this->glRenderObject = std::make_unique<GLRenderObject>(*glRenderObject);
}


std::ostream& operator<<(
    std::ostream& os,
    const shapegame::RenderPackage& rp
) {
    std::cout << "Shape:" << std::endl;
    std::cout << '\t';
    std::cout << "_height: ";
    std::cout << rp.shape->_height << std::endl;
    return os;
}