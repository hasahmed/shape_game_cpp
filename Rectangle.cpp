#include "shapegame"

using namespace shapegame;

Rectangle::Rectangle(
	float width,
	float height,
	Position pos,
	Color color
) : MultiShape(pos) {
	Triangle *firstTriangle = new Triangle(
		Position(pos.getX(), pos.getY() + height),
		Point(pos),
		Point(pos.getX() + width, pos.getY() + height),
		color
	);
	Triangle *secondTriangle = new Triangle(
		Position(pos),
		Point(pos.getX() + width, pos.getY()),
		Point(pos.getX() + width, pos.getY() + height),
		color
	);
	this->shapes.push_back(firstTriangle);
	this->shapes.push_back(secondTriangle);
}
Rectangle::~Rectangle() {
	// std::cout << "Rect Killed" << std::endl;
}

// Rectangle(): Rectangle(0, 0, Position(), Color()) {}