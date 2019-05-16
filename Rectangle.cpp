#include "shapegame"

using namespace shapegame;

Rectangle::Rectangle(
	float width,
	float height,
	Position pos,
	Color color
) : MultiShape(pos) {
	auto firstTriangle = std::make_unique<Triangle>(
		Position(pos.getX(), pos.getY() + height),
		Point(pos),
		Point(pos.getX() + width, pos.getY() + height),
		color
	);
	std::unique_ptr<Triangle> secondTriangle = std::make_unique<Triangle>(
		Position(pos),
		Point(pos.getX() + width, pos.getY()),
		Point(pos.getX() + width, pos.getY() + height),
		color
	);
	this->addShape(std::move(firstTriangle));
	this->addShape(std::move(secondTriangle));
}

Rectangle::~Rectangle() {
	#if PRINT_DESTRUCTION
	std::cout << "Rect Killed" << std::endl;
	#endif
}

// Rectangle(): Rectangle(0, 0, Position(), Color()) {}