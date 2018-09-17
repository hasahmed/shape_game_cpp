#include "shapegame"
shapegame::Shape::Shape(Position pos, Color color) :
    Object(pos),
    _color(color) {}


shapegame::Shape::Shape(Color color) :
    Object(0.0, 0.0),
    _color(color) {}
