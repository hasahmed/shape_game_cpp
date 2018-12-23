#include "shapegame"
#include <unordered_set>
using namespace shapegame;
SimpleCollision::SimpleCollision() : shapeStore(), currentlyColliding_() {
}

std::vector<ShapePair> SimpleCollision::findContaining(Shape *shape) {
	std::vector<ShapePair> ret;
	for (auto sp : this->currentlyColliding_) {
		if (sp.first == shape || sp.second == shape) {
			ret.push_back(sp);
		}
	}
	return ret;
}
void SimpleCollision::add(Shape* shape) {
		this->shapeStore.insert(shape);
}
void SimpleCollision::clear() {
	this->shapeStore.clear();
}
void SimpleCollision::remove(Shape *shape) {
	std::vector<ShapePair> collisions = this->findContaining(shape);
	for (auto sp : collisions) {
		this->currentlyColliding_.erase(sp);
	}
	this->shapeStore.erase(shape);
}
void SimpleCollision::check() {
	using namespace std;
	for (auto shapei : this->shapeStore) {
		for (auto shapej : this->shapeStore) {
			if (shapej != shapei) {
				if (
					shapej != shapei &&
					shapej->isColliding(*(shapei))
				) {
					ShapePair colliding(shapei, shapej);
					auto inserted = this->currentlyColliding_.insert(colliding);
					if (inserted.second) {
						colliding.first->onCollisionStart(*colliding.second);
						colliding.second->onCollisionStart(*colliding.first);
					} else {
						colliding.first->onColliding(*colliding.second);
						colliding.second->onColliding(*colliding.first);
					}
				}
			}
		}
	}
	std::unordered_set<ShapePair> notRemoved;
	for (auto &sPair : this->currentlyColliding_) {
		if (!sPair.first->isColliding(*sPair.second)) {
			sPair.first->onCollisionStop(*sPair.second);
			sPair.second->onCollisionStop(*sPair.first);
		} else {
			notRemoved.insert(sPair);
		}
	}
	this->currentlyColliding_ = notRemoved;
}