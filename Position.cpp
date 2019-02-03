#include "shapegame"
using namespace shapegame;

Position::Position(float x, float y, Dirtyable *onwer) : Point(x, y), owner(owner) {}
Position::Position(float x, float y) : Point(x, y), owner(nullptr) {}
Position::Position(Point pos, Dirtyable *owner): Position(pos.getX(), pos.getY(), owner) {}
Position::Position(Point pos): Position(pos.getX(), pos.getY(), nullptr) {}
Position::Position(Dirtyable *owner): Position(0, 0, owner) {}
Position::Position(): Position(0, 0, nullptr) {}
void Position::setX(const float x){
	if (this->owner) {
		this->owner->setDirty(true);
	}
	Point::setX(x);
}
void Position::setY(const float y){
	if (this->owner) {
		this->owner->setDirty(true);
	}
	Point::setY(y);
}
