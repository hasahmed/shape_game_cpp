#include "shapegame"

shapegame::Position::Position(float x, float y) : _x(x), _y(y) {}
float shapegame::Position::x() const {return this->_x;}
float shapegame::Position::y() const {return this->_y;}
void shapegame::Position::setX(const double x){
	this->_x = x;
}
void shapegame::Position::setY(const double y){
	this->_y = y;
}
