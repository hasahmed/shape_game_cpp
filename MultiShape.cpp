#include "shapegame"
using namespace shapegame;

MultiShape::MultiShape(Shape& mainShape, std::vector<Shape*>& shapes): Shape(mainShape) {
}
void MultiShape::onAdd(){
	for (Shape& s : this->shapes) {
		Game::inst().scene->addChild(&s);
	}
}
void MultiShape::onKill() {}
void MultiShape::onRemove() {}
void MultiShape::setPosition(double x, double y) {}