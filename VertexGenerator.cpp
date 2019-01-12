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

std::vector<float> shapegame::VertexGenerator::triangleVerts(const Shape& shape) {
    try {
        Shape *nonConstShape = const_cast<Shape*>(&shape);
        Triangle *t = dynamic_cast<Triangle*>(nonConstShape);
        float x1 = this->xPxToGl(t->pos.getX());
        float y1 = this->yPxToGl(t->pos.getY());
        float x2 = this->xPxToGl(t->second.getX());
        float y2 = this->yPxToGl(t->second.getY());
        float x3 = this->xPxToGl(t->third.getX());
        float y3 = this->yPxToGl(t->third.getY());

        // using namespace std;
        // cout << "x1: " << x1 << endl;
        // cout << "x3: " << x3 << endl;
        // cout << (x1 == x3) << endl;
        // cout << t->pos.getX() << endl;
        // cout << t->third.getX() << endl;

        return std::vector<float>{
            x1, y1, 0.0f, //lower left,
            x2, y2, 0.0f, //lower right
            x3, y3, 0.0f, // top left
        };
    } catch (std::bad_cast e) {
        throw std::runtime_error("Shape should be a triangle");
    }
}
std::vector<float> shapegame::VertexGenerator::circleVerts(const Shape &shape) {
    throw std::runtime_error("Not Implemented");
}
std::vector<float> shapegame::VertexGenerator::rectangleVerts(const Shape &shape) {

    float x = this->xPxToGl(shape.pos.getX());
    float y = this->yPxToGl(shape.pos.getY());
    float xsize = shape.getWidth() * horPxStep();
    float ysize = shape.getHeight() * vertPxStep();

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
float shapegame::VertexGenerator::horPxStep() {
    return 2.0f / (float)this->_window->getWidth();
}
float shapegame::VertexGenerator::vertPxStep() {
    return 2.0f / (float)this->_window->getHeight();
}

shapegame::VertexGenerator* shapegame::VertexGenerator::instance() {
    if (!VertexGenerator::_instance)
        throw std::runtime_error("Error: No instance has yet been created");
    return VertexGenerator::_instance;
}

float VertexGenerator::yPxToGl(float coord) {
    return 1.0f - (coord * this->vertPxStep());
}
float VertexGenerator::xPxToGl(float coord) {
    return -1.0f + (coord * this->horPxStep());
}
Point VertexGenerator::pxToGl(float x, float y) {
    return Point(x, y);
}
Point VertexGenerator::pxToGl(Point coords) {
    return coords;
}