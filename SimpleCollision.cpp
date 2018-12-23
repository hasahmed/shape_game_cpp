#include "shapegame"
#include <unordered_set>
using namespace shapegame;
SimpleCollision::SimpleCollision() : shapeStore_(), currentlyColliding_() {
	this->shapeStore_.reserve(100);
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
		this->shapeStore_.push_back(shape);
		this->shapeStore.insert(shape);
}
void SimpleCollision::clear() {
	this->shapeStore_.clear();
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
	for (unsigned int i = 0; i < this->shapeStore_.size(); i++) {
		for (unsigned int j = 0; j < this->shapeStore_.size(); j++) {
			if (this->shapeStore_[j] != this->shapeStore_[i]) {
				if (
					this->shapeStore_[j] != this->shapeStore_[i] &&
					this->shapeStore_[j]->isColliding(*(this->shapeStore_[i]))
				) {
					ShapePair colliding(this->shapeStore_[i], this->shapeStore_[j]);
					// colliding.first->onCollisionStart(*colliding.second);
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
	// note that need to handle when shapes get deleted after collide
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