#include "shapegame"

using namespace shapegame;

TriangleIsosceles::TriangleIsosceles(float width, float height, Position pos, Color color) :
	Triangle(Point(0, 0), Point(width / 2, -height), Point(width, 0), color) {
		this->setPosition(pos);
	}
