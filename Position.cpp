#include "shapegame"

shapegame::Position::Position(float x, float y) : _x(x), _y(y) {}
float shapegame::Position::x() {return _x;}
float shapegame::Position::y() {return _y;}
