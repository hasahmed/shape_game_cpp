#include "shapegame"

shapegame::Position::Position(float x, float y) : _x(x), _y(y) {}
float shapegame::Position::getX() const {return this->_x;}
float shapegame::Position::getY() const {return this->_y;}
void shapegame::Position::setX(const double x){
	this->_x = x;
}
shapegame::Position::Position(): Position(0, 0) {}
void shapegame::Position::setY(const double y){
	this->_y = y;
}
