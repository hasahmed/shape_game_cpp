#include <stdexcept>
#include "shapegame"

using namespace shapegame;

Triangle::Triangle(Position first, Point second, Point third, Color color):
	Shape(0, 0, ShapeType::Triangle, first, color), second(second), third(third){}

Triangle::Triangle( Position first, Point second, Point third):
	Triangle(first, second, third, Color::BLACK) {}

void Triangle::update(){}
void Triangle::onAdd(){}
void Triangle::onKeyPress(int key, int action){}

void Triangle::translate(double x, double y) {
	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
}
void Triangle::translate(Position pos){
    this->translate(pos.getX(), pos.getY());
}
void Triangle::setPosition(double x, double y){
	float xDiff = x - this->pos.getX();
	float yDiff = y - this->pos.getY();

	int numPoints = 2;

	Point *points[numPoints] = {
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
	this->_dirty = true;
}
void Triangle::setPosition(Position pos){
    this->setPosition(pos.getX(), pos.getY());
}