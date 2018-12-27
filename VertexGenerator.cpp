#include <vector>
#include <stdexcept>
#include "shapegame"

using namespace shapegame;

shapegame::VertexGenerator* shapegame::VertexGenerator::_instance = NULL;

std::vector<float> shapegame::VertexGenerator::generate(const Shape &shape) {
    switch (shape.type) {
        case ShapeType::Triangle:
            return triangleVerts(shape);
        case ShapeType::Rectangle:
            return rectangleVerts(shape);
        case ShapeType::Circle:
            return {};
    }
    throw std::invalid_argument(
        std::string("The shape must of a type of Triangle, Square, or Circle but was ") + std::to_string((int)shape.type)
        );
}

std::vector<float> shapegame::VertexGenerator::triangleVerts(const Shape &shape) {
    // throw std::runtime_error("Not Implemented");
    // return std::vector<float>{
    // };
}
std::vector<float> shapegame::VertexGenerator::circleVerts(const Shape &shape) {
    float x = -1.0f + shape.pos.getX() * getHorizontalPixelStep();
    float y = 1.0f - shape.pos.getY() * getVerticalPixelStep();
    throw std::runtime_error("Not Implemented");
    return std::vector<float>{
        x, y, 0.0f, //lower left,
        x, 0.0f, 0.0f, //lower right
        x, y, 0.0f, // top left
    };
}
std::vector<float> shapegame::VertexGenerator::rectangleVerts(const Shape &shape) {

    float x = -1.0f + shape.pos.getX() * getHorizontalPixelStep();
    float y = 1.0f - shape.pos.getY() * getVerticalPixelStep();
    float xsize = shape.getWidth() * getHorizontalPixelStep();
    float ysize = shape.getHeight() * getVerticalPixelStep();

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
    return 2.0f / (float)this->_window->getWidth();
}
float shapegame::VertexGenerator::getVerticalPixelStep() {
    return 2.0f / (float)this->_window->getHeight();
}

shapegame::VertexGenerator* shapegame::VertexGenerator::instance() {
    if (!VertexGenerator::_instance)
        throw std::runtime_error("Error: No instance has yet been created");
    return VertexGenerator::_instance;
}

float VertexGenerator::pxToGl(float coord) {
    return 1.0f;
}
Point VertexGenerator::pxToGl(Point coords) {
    return coords;
}