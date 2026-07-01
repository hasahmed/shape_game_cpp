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
	float centerX = (this->pos.getX() + this->second.getX() + this->third.getX()) / 3;
	float centerY = (this->pos.getY() + this->second.getY() + this->third.getY()) / 3;
	return Point(centerX, centerY);
}

Triangle::Triangle(Point first, Point second, Point third, Color color):
	Shape(0, 0, ShapeType::Triangle, first, color), second(second), third(third) {
		this->name = "Triangle";
	}

Triangle::Triangle( Point first, Point second, Point third):
	Triangle(first, second, third, Color::BLACK) {}
Triangle::Triangle(): Triangle(Point(), Point(), Point(), Color::NIL) {}
void Triangle::setPosition(float x, float y){
	float xDiff = x - this->pos.getX();
	float yDiff = y - this->pos.getY();

	int numPoints = 2;

	Point *points[] = {
		&this->second,
		&this->third
	};
	this->pos.setX(x);
	this->pos.setY(y);
	for (int i = 0; i < numPoints; i++) { // skip the first
		Point& newP = *points[i];
		newP.setX(newP.getX() + xDiff);
		newP.setY(newP.getY() + yDiff);
	}
}
