#include "shapegame"

using namespace shapegame;
using namespace shapegame::Input;
Object::Object(double x, double y) : pos(x, y) {}
Object::Object(Position pos) : pos(pos) {}
Object::~Object(){
	// std::cout <<"deleted: Object" <<std::endl;
}
void Object::kill() {
	this->onKill();
	this->canKill = true;
}
void Object::onAdd(){}
void Object::update(){}
void Object::onKill(){}
void Object::onRemove(){}
void Object::onKeyPress(Kb::Key key, Input::Action action){}
void Object::onMouseClick(Mouse::Btn btn, Input::Action action){}