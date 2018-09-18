#include <memory>
#include "shapegame"

shapegame::RenderPackage::RenderPackage(Shape *shape,
        GLRenderObject *glRenderObject) {

    std::make_unique<Shape>(*shape);
    std::make_unique<GLRenderObject>(*glRenderObject);
}

