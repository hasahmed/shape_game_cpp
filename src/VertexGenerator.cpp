#define _USE_MATH_DEFINES
#include <vector>
#include <stdexcept>
#include <math.h>
#include "shapegame.hpp"

using namespace shapegame;

shapegame::VertexGenerator* shapegame::VertexGenerator::_instance = NULL;

void shapegame::VertexGenerator::generate(Shape &shape, float *verts) {
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

void scalePointX(Point &origin, Point &point, float scaleFactor) {
	if (point == origin) return;
	if (point.x == origin.x) return;
	point.x *= scaleFactor;
}
void scalePointY(Point &origin, Point &point, float scaleFactor) {
	if (point == origin) return;
	if (point.y == origin.y) return;
	// std::cout << "Here scaling y" << std::endl;
	// std::cout << "Y before: " << point.y << std::endl;
	point.y *= scaleFactor;
	// std::cout << "Y after: " << point.y << std::endl;

}
void scalePoint(Point &origin, Point &point, float scaleFactorX, float scaleFactorY) {
	scalePointX(origin, point, scaleFactorX);
	scalePointY(origin, point, scaleFactorY);
}
void scalePoint(Point &origin, Point &point, Point scaleFactors) {
	// std::cout << point << std::endl;
	// std::cout << origin << std::endl;
	scalePoint(origin, point, scaleFactors.x, scaleFactors.y);
}

void rotatePoint(Point &origin, Point &point, float rotationDegrees) {
    if (point == origin) return; 

    // rotation needs to start from 0 degrees, NOT whatever it was rotated to before
  float rotationRadians = rotationDegrees * (M_PI / 180);

  float s = sin(rotationRadians);
  float c = cos(rotationRadians);


  point.x -= origin.x;
  point.y -= origin.y;

  float xNew = point.x * c - point.y * s;
  float yNew = point.x * s + point.y * c;

  point.x = xNew + origin.x;
  point.y = yNew + origin.y;
}

void shapegame::VertexGenerator::triangleVerts(Shape& shape, float *verts) {
		Shape *nonConstShape = const_cast<Shape*>(&shape);
		Triangle *t = dynamic_cast<Triangle*>(nonConstShape);
		Object* rootObj = shape.getRoot();

		if (t) {
			// rotation
			if (rootObj->getNextRotation() != 0) {
                Point origin = rootObj->pos;
                RotationInfo& rotInfo = rootObj->getRotationInfo();
                if (rotInfo.hasAlternateOrigin) {
                    origin = rotInfo.alternateOrigin;
                }
                rotatePoint(origin, t->pos, rootObj->getNextRotation());
                rotatePoint(origin, t->second, rootObj->getNextRotation());
                rotatePoint(origin, t->third, rootObj->getNextRotation());

			}
			// scale
			if (Point scale = rootObj->getNextScale()) {
				Point currentScale = rootObj->getScale();
					if (currentScale != Point(1, 1)) {
						scale = Point(scale.x / currentScale.x, scale.y / currentScale.y);
					}
					std::cout << "Scale: " << scale << std::endl;

					scalePoint(rootObj->pos, t->pos, scale);
					scalePoint(rootObj->pos, t->second, scale);
					scalePoint(rootObj->pos, t->third, scale);

					t->recalculateSize();
					if (t->getParent()) {
						MultiShape *m = (MultiShape*)t->getParent();
						m->updateSize(*t);
					}
			}
			// translate
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