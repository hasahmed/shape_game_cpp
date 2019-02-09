#include "shapegame"
using namespace shapegame;

MultiShape::MultiShape(Position pos): Object(pos) {}

MultiShape::MultiShape(Object* controller, std::vector<Shape*>& shapes): Object(*controller) {
	using namespace std;
	for (Shape *s : shapes) {
		this->shapes.push_back(s);
	}
	// std::cout << "shapes.size(): " << shapes.size() << std::endl;
	// cout << *this << endl;
}
void MultiShape::onAdd(){
	// std::cout << "shapes.size(): " << this->shapes.size() << std::endl;
	for (Shape *s : this->shapes) {
		Game::inst().scene->addChild(s);
	}
}
void MultiShape::onKill() {}
void MultiShape::onRemove() {}
void MultiShape::setPosition(double x, double y) {
	auto changeInX = x - this->pos.getX();
	auto changeInY = y - this->pos.getY();
	Object::setPosition(x, y);
	for (Shape *s : this->shapes) {
		// std::cout << "HERE" << std::endl;
		// exit(0);
		s->translate(changeInX, changeInY);
	}
}
// void MultiShape::translate(float x, float y) {
// 	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
// }