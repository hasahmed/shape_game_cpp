#include "shapegame"
using namespace shapegame;
shapegame::Shape::Shape(
        float height,
        float width,
        ShapeType type,
        Position pos,
        Color color
        ) :
            Object(pos),
            _height(height),
            _width(width),
            color(color),
            type(type) {}

Shape::Shape(float height, float width, ShapeType type, Color color) :
    Shape(height, width, type, Position(0.0, 0.0), color) {}
float Shape::getHeight() const {return this->_height;}
float Shape::getWidth() const {return this->_width;}

void Shape::setPosition(double x, double y){
    this->pos.setX(x);
    this->pos.setY(y);
    this->_dirty = true;
}
void Shape::setPosition(Position pos){
    this->setPosition(pos.getX(), pos.getY());
}

void Shape::translate(double x, double y) {
    this->pos.setX(this->pos.getX() + x);
    this->pos.setY(this->pos.getY() + y);
    this->_dirty = true;
}
void Shape::translate(Position pos){
    this->translate(pos.getX(), pos.getY());
}