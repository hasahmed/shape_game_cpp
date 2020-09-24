#include "shapegame.hpp"
using namespace shapegame;

Square::Square(Point pos, float size): Rectangle(size, size, pos, Color::BLACK) {}
Square::Square(Point pos, float size, Color color): Rectangle(size, size, pos, color) {}