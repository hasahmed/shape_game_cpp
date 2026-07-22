#include <stdexcept>
#include <vector>
#include <algorithm>
#include "shapegame.hpp"

using namespace shapegame;

Triangle::~Triangle(){
	#if PRINT_DESTRUCTION
	std::cout << "Triangle Killed" << std::endl;
	#endif
}

Point Triangle::getCenter() {
	float centerX = (this->first.getX() + this->second.getX() + this->third.getX()) / 3;
	float centerY = (this->first.getY() + this->second.getY() + this->third.getY()) / 3;
	return Point(centerX, centerY);
}
Point Triangle::getOrigin() {
	return this->getCenter();
}

Triangle::Triangle(Point first, Point second, Point third, Color color):
	Shape(0, 0, ShapeType::Triangle, first, color), second(second), third(third) {
		this->name = "Triangle";
	}

Triangle::Triangle( Point first, Point second, Point third):
	Triangle(first, second, third, Color::BLACK) {}
Triangle::Triangle(): Triangle(Point(), Point(), Point(), Color::NIL) {}
void Triangle::setPosition(float x, float y) {
	/*
		This determines world-position coorinates of each of the triangles points
	 */
	// float xDiff = x - this->first.getX();
	// float yDiff = y - this->first.getY();
	float xDiff = x - this->getOrigin().x;
	float yDiff = y - this->getOrigin().y;

	int numPoints = 3;

	Point *points[] = {
		&this->first,
		&this->second,
		&this->third
	};
	// this->first.setX(x);
	// this->first.setY(y);
	// this->pos.setX(x);
	// this->pos.setY(y);
	for (int i = 0; i < numPoints; i++) { // skip the first
		Point& newP = *points[i];
		newP.setX(newP.getX() + xDiff);
		newP.setY(newP.getY() + yDiff);
	}
	this->pos = this->getCenter();
}
