#include "shapegame"
#include <unordered_set>
using namespace shapegame;
SimpleCollision::SimpleCollision() : shapeStore_(), currentlyColliding_() {
	this->shapeStore_.reserve(100);
}
void SimpleCollision::add(Shape* shape) {
		this->shapeStore_.push_back(shape);
}
void SimpleCollision::clear() {
	this->shapeStore_.clear();
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
					std::pair<Shape*, Shape*> collides(this->shapeStore_[i], this->shapeStore_[j]);
					ShapePair colliding(this->shapeStore_[i], this->shapeStore_[j]);
					collides.first->onCollisionStart(*collides.second);
					this->currentlyColliding_.insert(colliding);
				}
			}
		}
	}
	std::unordered_set<ShapePair> notRemoved;
	// cout << "Sizeof currentlyColliding_: " << currentlyColliding_.size() << endl;
	for (auto &sPair : this->currentlyColliding_) {
		// cout << "Pair: " << &sPair << endl;
		// cout << '\t' << "first : " << sPair.first << endl;
		// cout << '\t' << "second: " << sPair.second << endl << endl;
		if (!sPair.first->isColliding(*sPair.second)) {
			puts("No longer colliding");
		} else {
			notRemoved.insert(sPair);
		}
	}
	this->currentlyColliding_ = notRemoved;
}