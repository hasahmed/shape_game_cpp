#include "shapegame"
using namespace shapegame;

MultiShape::MultiShape(Shape* mainShape, std::vector<Shape*>& shapes): Triangle() {
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
void MultiShape::setPosition(double x, double y) {}