#include "shapegame"
using namespace shapegame;

MultiShape::MultiShape(Shape* mainShape, std::vector<Shape*>& shapes): Shape(*mainShape) {
	using namespace std;
	for (Shape *s : shapes) {
		this->shapes.push_back(s);
	}
	cout << *this << endl;
}
void MultiShape::onAdd(){
	for (Shape *s : this->shapes) {
		Game::inst().scene->addChild(s);
	}
}
void MultiShape::onKill() {}
void MultiShape::onRemove() {}
void MultiShape::setPosition(double x, double y) {}