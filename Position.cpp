#include "shapegame"
using namespace shapegame;

Position::Position(float x, float y, Dirtyable *owner) : Point(x, y), owner_(owner) {}
Position::Position(float x, float y) : Point(x, y), owner_(nullptr) {}
Position::Position(Point pos, Dirtyable *owner): Position(pos.getX(), pos.getY(), owner) {}
Position::Position(Point pos): Position(pos.getX(), pos.getY(), nullptr) {}
Position::Position(Dirtyable *owner): Position(0, 0, owner) {}
Position::Position(): Position(0, 0, nullptr) {}
void Position::setX(const float x){
	if (this->owner_) {
		this->owner_->setDirty(true);
	}
	Point::setX(x);
}
void Position::setY(const float y){
	if (this->owner_) {
		this->owner_->setDirty(true);
	}
	Point::setY(y);
}
