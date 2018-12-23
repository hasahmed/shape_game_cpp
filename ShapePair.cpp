#include "shapegame"
using namespace shapegame;
ShapePair::ShapePair(){};
ShapePair::ShapePair(Shape *first, Shape *second): first(first), second(second){}

bool ShapePair::operator==(const ShapePair &other) const {
	return
		(this->first == other.first && this->second == other.second) ||
		(this->first == other.second && this->second == other.first);
}
