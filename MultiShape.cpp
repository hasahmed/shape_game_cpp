#include "shapegame"
#include <memory>
using namespace shapegame;


MultiShape::MultiShape(Position pos): Entity(pos) {}
// MultiShape::MultiShape(Object* controller, std::vector<Object*>& shapes): Entity(*controller) {
// 	using namespace std;
// 	for (Object *s : shapes) {
// 		this->shapes.push_back(s);
// 	}
// 	// std::cout << "shapes.size(): " << shapes.size() << std::endl;
// 	// cout << *this << endl;
// }
void MultiShape::onAdd(){
	// std::cout << "shapes.size(): " << this->shapes.size() << std::endl;
	for (auto &s : this->unAddedShapes) {
		auto sRaw = s.release();
		this->shapes.push_back(sRaw);
		Game::inst().scene->addChild(sRaw);
	}
	this->unAddedShapes.clear();
}
void MultiShape::addShape(std::unique_ptr<Object> shape) {
	shape->setZOrder(this->getZOrder());
	this->unAddedShapes.push_back(std::move(shape));
}
void MultiShape::addShape(Object* shape) {
	this->addShape(std::unique_ptr<Object>(shape));
	// this->unAddedShapes.push_back(std::unique_ptr<Object>(shape));
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
		// std::cout << "HERE" << std::endl;
		// exit(0);
		s->setPosition(s->pos.getX() + changeInX, s->pos.getY() + changeInY);
		// s->translate(changeInX, changeInY);
	}
}
void MultiShape::onKill() {
	for (Object *s : this->shapes) {
		s->kill();
	}
}
// void MultiShape::translate(float x, float y) {
// 	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
// }