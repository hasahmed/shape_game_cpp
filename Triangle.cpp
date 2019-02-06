#include <stdexcept>
#include <vector>
#include <algorithm>
#include "shapegame"

using namespace shapegame;

Triangle::Triangle(Position first, Point second, Point third, Color color):
	Shape(0, 0, ShapeType::Triangle, first, color), second(second), third(third) {

		// find point mp with min x
		// collisionPosition = (minX, mp.y + maxY)
		// width = maxX - minX;
		// height = maxY - minY;

		//this->collisionRect = new Rectangle(collisionPosition, width, height);

		std::vector<Point*> verts {
			&this->pos,
			&this->second,
			&this->third
		};
		Point minXPoint = this->pos;
		float maxX = this->pos.getX();
		float minX = this->pos.getX();
		float maxY = this->pos.getY();
		float minY = this->pos.getY();
		for_each(verts.begin(), verts.end(), [
			&minXPoint,
			&maxX,
			&minX,
			&maxY,
			&minY
			](Point *p){
				if (p->getX() < minXPoint.getX()) {
					minXPoint = *p;
				}
				maxX = std::max<float>(maxX, p->getX());
				minX = std::min<float>(minX, p->getX());
				maxY = std::max<float>(maxY, p->getY());
				minY = std::min<float>(minY, p->getY());
		});
		this->_height = maxX - minX;
		this->_width = maxY - minY;
		this->collisionPosition = Position(minX, minXPoint.getY() + maxY);
	}

Triangle::Triangle( Position first, Point second, Point third):
	Triangle(first, second, third, Color::BLACK) {}
Triangle::Triangle(): Triangle(Point(), Point(), Point(), Color::NIL) {}

void Triangle::translate(double x, double y) {
	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
}
void Triangle::translate(Position pos){
    this->translate(pos.getX(), pos.getY());
}
void Triangle::setPosition(double x, double y){
	float xDiff = x - this->pos.getX();
	float yDiff = y - this->pos.getY();

	int numPoints = 2;

	Point *points[] = {
		&this->second,
		&this->third
	};
	this->pos.setX(x);
	this->pos.setY(y);
	for (int i = 0; i < numPoints; i++) { // skip the first
		Point& newP = *points[i];
		newP.setX(newP.getX() + xDiff);
		newP.setY(newP.getY() + yDiff);
	}
}
void Triangle::setPosition(Position pos){
    this->setPosition(pos.getX(), pos.getY());
}