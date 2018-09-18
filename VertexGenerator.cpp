#include <vector>
#include <stdexcept>
#include "shapegame"

shapegame::VertexGenerator* shapegame::VertexGenerator::_instance = NULL;

std::vector<float> shapegame::VertexGenerator::generate(Shape &shape) {
    switch (shape.type) {
        case ShapeType::Triangle:
            return triangleVerts(shape);
        case ShapeType::Rectangle:
            return {};
        case ShapeType::Circle:
            return {};
    }
    throw std::invalid_argument(
            "The shape must of a type of Triangle, Square, or Circle");
}

std::vector<float> shapegame::VertexGenerator::triangleVerts(Shape &shape) {
    return std::vector<float>{

    };
}
std::vector<float> shapegame::VertexGenerator::rectangleVerts(Shape &shape) {



    float x = -1.0f + shape.pos.x() * getHorizontalPixelStep();
    float y = 1.0f - shape.pos.y() * getVerticalPixelStep();
    float xsize = shape.width() * getHorizontalPixelStep();
    float ysize = shape.height() * getVerticalPixelStep();

    return std::vector<float>{
        x,              y - ysize,   0.0f, //lower left,
        x + xsize,      y - ysize,   0.0f, //lower right
        x,              y,           0.0f, // top left


            // triangle 2
        x,              y,           0.0f, // top left
        x + xsize,      y - ysize,   0.0f, //lower right
        x + xsize,      y,           0.0f //lower right
    };
}

shapegame::VertexGenerator::VertexGenerator(Window *window) : _window(window) {
    shapegame::VertexGenerator::_instance = this;
}
float shapegame::VertexGenerator::getHorizontalPixelStep() {
    return 2.0f / (float)this->_window->height();
}
float shapegame::VertexGenerator::getVerticalPixelStep() {
    return 2.0f / (float)this->_window->width();
}

shapegame::VertexGenerator* shapegame::VertexGenerator::instance() {
    if (!VertexGenerator::_instance)
        throw std::runtime_error("Error: No instance has yet been created");
    return VertexGenerator::_instance;
}
