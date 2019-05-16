#include "shapegame"
using namespace shapegame;


MultiShape::MultiShape(Position pos): Entity(pos) {}
void MultiShape::onAdd(){}
/* BASE IMPL */
void MultiShape::addShape(std::unique_ptr<Object> shape) {
	Object *s = shape.get();
	s->setParent(this);
	this->shapes.push_back(s);
	this->shapeStorage.push_back(std::move(shape));
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
		if (s) {
			s->setPosition(s->pos.getX() + changeInX, s->pos.getY() + changeInY);
		} else {
			throw std::runtime_error("None of the shapes in the multishape should be null");
		}
	}
}
void MultiShape::onKill() {}

std::vector<Object*>& MultiShape::getShapes() {
	return this->shapes;
}

MultiShape::~MultiShape() {
	#if PRINT_DESTRUCTION
	std::cout << "MultiShape Killed" << std::endl;
	#endif
}