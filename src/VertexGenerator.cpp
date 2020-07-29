#include <vector>
#include <stdexcept>
#include "shapegame.hpp"

using namespace shapegame;

shapegame::VertexGenerator* shapegame::VertexGenerator::_instance = NULL;

void shapegame::VertexGenerator::generate(const Shape &shape, float *verts) {
    switch (shape.type) {
        case ShapeType::Triangle:
            return triangleVerts(shape, verts);
        // case ShapeType::Rectangle:
        //     return rectangleVerts(shape, verts);
        // case ShapeType::Circle:
				// 	return circleVerts(shape, verts);
				default:
					throw std::invalid_argument(
							std::string(
								"The shape must of a type of Triangle, Square, Circle, or Multi, but was ") +
								std::to_string((int)shape.type)
							);
    }
}

void shapegame::VertexGenerator::triangleVerts(const Shape& shape, float *verts) {
		Shape *nonConstShape = const_cast<Shape*>(&shape);
		Triangle *t = dynamic_cast<Triangle*>(nonConstShape);
		if (t) {
			if (shape.getRotation() != 0) {
				// apply rotation to each vertex first
				// need an origin to rotate around
				// I suppose pos.x,y
			}
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

    } else {
			throw std::runtime_error("Shape should be a triangle");
    }
}
// void shapegame::VertexGenerator::circleVerts(const Shape &shape, std::vector<float> &verts) {
//     throw std::runtime_error("Not Implemented");
// }
// void shapegame::VertexGenerator::rectangleVerts(const Shape &shape, std::vector<float> &verts) {

//     float x = this->xPxToGl(shape.pos.getX());
//     float y = this->yPxToGl(shape.pos.getY());
//     float xsize = shape.getWidth() * horPxStep();
//     float ysize = shape.getHeight() * vertPxStep();
// }

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