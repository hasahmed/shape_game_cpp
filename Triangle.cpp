#include <stdexcept>
#include "shapegame"

using namespace shapegame;

Triangle::Triangle(
Position first,
Point second,
Point third,
Color color) : Shape(0, 0, ShapeType::Triangle, first, color){}

void Triangle::update(){}
void Triangle::onAdd(){}
void Triangle::onKeyPress(int key, int action){}