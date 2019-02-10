#include "shapegame"

using namespace shapegame;

Quad::Quad(Position p1, Point p2, Point p3, Point p4, Color color) : MultiShape(p1) {
	auto t1 = new Triangle(p1, p2, p3, color);
	auto t2 = new Triangle(p1, p3, p4, color);
	this->addShape(t1);
	this->addShape(t2);
}