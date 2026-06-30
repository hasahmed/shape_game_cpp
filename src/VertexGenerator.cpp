#define _USE_MATH_DEFINES
#include <vector>
#include <stdexcept>
#include <cassert>
#include <math.h>
#include "shapegame.hpp"

using namespace shapegame;

shapegame::VertexGenerator* shapegame::VertexGenerator::_instance = NULL;

void shapegame::VertexGenerator::generate(Shape &shape, float *verts) {
    switch (shape.type) {
        case ShapeType::Triangle:
            return triangleVerts(shape, verts);
				default:
					throw std::invalid_argument(
							std::string(
								"The shape must of a type of Triangle, Square, Circle, or Multi, but was ") +
								std::to_string((int)shape.type)
							);
    }
}

// So we generate verticies every frame?
void shapegame::VertexGenerator::triangleVerts(Shape& shape, float *verts) {
		Shape *nonConstShape = const_cast<Shape*>(&shape);
		Triangle *t = dynamic_cast<Triangle*>(nonConstShape);
		Object* rootObj = shape.getRoot();
		assert(t && "Triangle should not be null");
		// SRT: scale, rotate, translate

		float x1 = this->xPxToGl(t->pos.getX());
		float y1 = this->yPxToGl(t->pos.getY());
		float x2 = this->xPxToGl(t->second.getX());
		float y2 = this->yPxToGl(t->second.getY());
		float x3 = this->xPxToGl(t->third.getX());
		float y3 = this->yPxToGl(t->third.getY());

		verts[0] = x1;
		verts[1] = y1;
		verts[2] = 0.0f;

		verts[3] = x2;
		verts[4] = y2;
		verts[5] = 0.0f;

		verts[6] = x3;
		verts[7] = y3;
		verts[8] = 0.0f;
}

shapegame::VertexGenerator::VertexGenerator(IWindow *window) : _window(window) {
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