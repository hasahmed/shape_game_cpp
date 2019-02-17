#include "shapegame"
using namespace shapegame;


MultiShape::MultiShape(Position pos): Entity(pos) {}
void MultiShape::onAdd(){}
void MultiShape::onMultiAdd(){
	this->unAddedShapes.clear();
}
void MultiShape::addShape(std::unique_ptr<Object> shape) {
	this->unAddedShapes.push_back(std::move(shape));
	this->shapes.push_back(shape.get());
}
void MultiShape::addShape(Object* shape) {
	this->addShape(std::unique_ptr<Object>(shape));
}
void MultiShape::setZOrder(int zOrder) {
	Object::setZOrder(zOrder);
	for (Object *s : this->shapes) {
		s->setZOrder(zOrder);
	}
}
void MultiShape::setPosition(Point pos) {
	this->setPosition(pos.getX(), pos.getY());
}
void MultiShape::setPosition(float x, float y) {
	auto changeInX = x - this->pos.getX();
	auto changeInY = y - this->pos.getY();
	Object::setPosition(x, y);
	for (Object *s : this->shapes) {
		s->setPosition(s->pos.getX() + changeInX, s->pos.getY() + changeInY);
	}
}
void MultiShape::onKill() {}
MultiShape::~MultiShape() {
	#if PRINT_DESTRUCTION
	std::cout << "MultiShape Killed" << std::endl;
	#endif
}