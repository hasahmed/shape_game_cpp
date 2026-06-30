#include "shapegame.hpp"
#include <algorithm>
using namespace shapegame;


MultiShape::MultiShape(): Entity(Point()) {
	this->name = "MultiShape";
}
MultiShape::MultiShape(Point pos): Entity(pos) {
	this->name = "MultiShape";
}


/* BASE IMPL */
void MultiShape::addShape(std::unique_ptr<Object> obj) {
	obj->setParent(this);

	if (this->isInScene()) {
		this->unAddedObjects.emplace_back(obj.get());
		this->hasUnaddedObjects = true;
	}

	this->shapeStorage.emplace_back(std::move(obj));
}
void MultiShape::addShape(Object* obj) {
	this->addShape(std::unique_ptr<Object>(obj));
}
void MultiShape::setPosition(Point pos) {
	this->setPosition(pos.getX(), pos.getY());
}
void MultiShape::setPosition(float x, float y) {
	auto changeInX = x - this->pos.getX();
	auto changeInY = y - this->pos.getY();
	Object::setPosition(x, y);
	for (Object *s : this->getShapes()) {
		if (s) {
			s->setPosition(s->pos.getX() + changeInX, s->pos.getY() + changeInY);
		} else {
			throw std::runtime_error("None of the shapes in the multishape should be null");
		}
	}
}

std::vector<Object*>& MultiShape::getShapes() {
	this->shapes.clear(); // clear in case any shapes have been
	// added or removed
	for (auto &shape : this->shapeStorage) {
		this->shapes.emplace_back(shape.get());
	}
	return this->shapes;
}
bool MultiShape::removeShape(Object *obj) {
	auto *children = &this->shapeStorage;
	for (auto it = children->begin(); it != children->end(); ++it) {
		if (it->get() == obj) {
			this->shapeStorage.erase(it);
			return true;
		}
	}
	return false;
}

MultiShape::~MultiShape() {
	#if PRINT_DESTRUCTION
	std::cout << "MultiShape Killed" << std::endl;
	#endif
}