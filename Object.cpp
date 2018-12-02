#include "shapegame"

using namespace shapegame;
Object::Object(double x, double y) : pos(x, y) {}
Object::Object(Position pos) : pos(pos) {}
Object::~Object(){
	std::cout <<"I have been killed" <<std::endl;
}
void Object::kill() {
	this->canKill = true;
}
void Object::onRemove(){}