#define _USE_MATH_DEFINES
#include <vector>
#include <stdexcept>
#include <cassert>
#include <math.h>
#include "shapegame.hpp"

using namespace shapegame;

shapegame::VertexGenerator* shapegame::VertexGenerator::_instance = NULL;

void shapegame::VertexGenerator::generateMesh(Shape &shape, float *verts) {
    switch (shape.type) {
        case ShapeType::Triangle:
            return triangleMesh(shape, verts);
				default:
					throw std::invalid_argument(
							std::string(
								"The shape must of a type of Triangle, Square, Circle, or Multi, but was ") +
								std::to_string((int)shape.type)
							);
    }
}

// So we generate verticies every frame?
void shapegame::VertexGenerator::triangleMesh(Shape& shape, float *verts) {
	Shape *nonConstShape = const_cast<Shape*>(&shape);
	Triangle *t = dynamic_cast<Triangle*>(nonConstShape);
	Object* rootObj = shape.getRoot();
	assert(t && "Triangle should not be null");
		// SRT: scale, rotate, translate

		// A problem:
		// Translation kind of happens immediately.
		// The position is 'updated' as soon as it happens,
		// therefore, the 'scale' and 'rotate' can't really happen
		// first because we don't know the old values?
		// WAIT WE DO have the old positions!
		// They're what currently reside in *verts!

		// So we currently overwrite previous verts because they're opengl
		// representation of the data, rather than our pixel representation


		// So alas the data we need we do not have...
		// effectivly the translation has already occurred
		// but why does that matter?
		// Seems like these opporations should NOT be in any way dependant on eachother
		float x1 = this->xPxToGl(t->first.getX());
		float y1 = this->yPxToGl(t->first.getY());
		float x2 = this->xPxToGl(t->second.getX());
		float y2 = this->yPxToGl(t->second.getY());
		float x3 = this->xPxToGl(t->third.getX());
		float y3 = this->yPxToGl(t->third.getY());

		verts[0] = x1;
		verts[1] = y1;

		verts[2] = x2;
		verts[3] = y2;

		verts[4] = x3;
		verts[5] = y3;
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