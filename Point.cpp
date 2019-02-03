#include "shapegame"
using namespace shapegame;
Point::Point(float x, float y) : _x(x), _y(y) {}
Point::Point(): Point(0, 0) {}
Point::~Point() {}
float Point::getX() const {return this->_x;}
float Point::getY() const {return this->_y;}
void Point::setX(const float x){
	this->_x = x;
}
void Point::setY(const float y){
	this->_y = y;
}