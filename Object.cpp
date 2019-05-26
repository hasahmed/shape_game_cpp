#include "shapegame"

using namespace shapegame;
using namespace shapegame::Input;
Object::Object(double x, double y) {
	this->pos = Position(x, y, this);
}
Object::Object() {}
Object::Object(Point pos) : Object(pos.getX(), pos.getY()) {}
Object::~Object(){
	#if PRINT_DESTRUCTION
	std::cout << "Object Killed" << std::endl;
	#endif
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
void Object::setPosition(float x, float y){
	this->pos.setX(x);
	this->pos.setY(y);
}
void Object::setPosition(Point pos) {
	this->setPosition(pos.getX(), pos.getY());
}
void Object::translate(float x, float y) {
	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
}
void Object::setDirty(bool dirty) {
	this->_dirty = dirty;
}
bool Object::isDirty() {
	return this->_dirty;
}

void Object::setParent(Object *parent) {
	this->_parent = parent;
}
Object* Object::getParent() {
	return this->_parent;
}
bool Object::isInScene() {
	return this->_inScene;
}