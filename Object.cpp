#include "shapegame"

using namespace shapegame;
using namespace shapegame::Input;
Object::Object(double x, double y) {
	this->pos = Position(x, y, this);
}
Object::Object() {}
Object::Object(Point pos) : Object(pos.getX(), pos.getY()) {}
Object::~Object(){}
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
void Object::setDirty(bool dirty) {
	this->_dirty = dirty;
}
bool Object::isDirty() {
	return this->_dirty;
}