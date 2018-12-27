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