#include "shapegame"

shapegame::Triangle::Triangle(
        int height,
        int width,
        double x,
        double y,
        Color color) :
    _height(height), _width(width), _pos(x, y), color(color) {}



shapegame::Triangle::Triangle(
        int height,
        int width,
        Position pos,
        Color color) :
    _height(height), _width(width), _pos(pos), color(color) {}
