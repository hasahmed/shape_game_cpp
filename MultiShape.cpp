#include "shapegame"
using namespace shapegame;

MultiShape::MultiShape(Position pos): Object(pos) {}

MultiShape::MultiShape(Object* controller, std::vector<Object*>& shapes): Object(*controller) {
	using namespace std;
	for (Object *s : shapes) {
		this->shapes.push_back(s);
	}
	// std::cout << "shapes.size(): " << shapes.size() << std::endl;
	// cout << *this << endl;
}
void MultiShape::onAdd(){
	// std::cout << "shapes.size(): " << this->shapes.size() << std::endl;
	for (Object *s : this->shapes) {
		s->zOrder = this->zOrder;
		if (s->zOrder > 0) 
			std::cout << s->zOrder << std::endl;
		Game::inst().scene->addChild(s);
	}
}
void MultiShape::addShape(Object* shape) {
	shape->zOrder = this->zOrder;
	this->shapes.push_back(shape);
}
void MultiShape::onRemove() {}
void MultiShape::setPosition(double x, double y) {
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