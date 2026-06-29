#include "shapegame.hpp"

using namespace shapegame;
using namespace shapegame::Input;
Object::Object(float x, float y) {
	this->pos = Point(x, y);
}
Object::Object() {}
Object::Object(Point pos) : Object(pos.getX(), pos.getY()) {}
Object::~Object(){
	#if PRINT_DESTRUCTION
	std::cout << "Object Killed" << std::endl;
	#endif
}

bool Object::recalculateSize() {
	// objects size never changes, its always (0, 0)
	return false;
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
float Object::getHeight() { return this->height; }
float Object::getWidth() { return this->width; }
Point Object::getSize() {return Point(this->width, this->height);}
void Object::setPosition(Point pos) {
	this->setPosition(pos.getX(), pos.getY());
}
void Object::translate(float x, float y) {
	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
}
void Object::translate(Point xy) {
	this->translate(xy.x, xy.y);
}
void Object::rotate(float degrees) {
	this->rotationInfo.nextRotation = degrees;
	this->rotationInfo.currentRotation += degrees;
}
void Object::rotateAround(float degrees, Point origin) {
	this->rotate(degrees);
	this->rotationInfo.hasAlternateOrigin = true;
	this->rotationInfo.alternateOrigin = origin;

}
void Object::rotateAround(float degrees, Object& origin) {
	this->rotateAround(degrees, origin.pos);
}
// current rotation == 2;
// degrees = 1
void Object::setRotation(float degrees) {
	this->rotationInfo.nextRotation = this->rotationInfo.currentRotation * -1;
	this->rotationInfo.nextRotation += degrees;
	this->rotationInfo.currentRotation = degrees;
}
float Object::getRotation() const {
	return this->rotationInfo.currentRotation;
}
float Object::getNextRotation() const {
	return this->rotationInfo.nextRotation;
}
RotationInfo& shapegame::Object::getRotationInfo()
{
	return this->rotationInfo;
}

void Object::setParent(Object *parent) {
	this->_parent = parent;
}
Object* Object::getParent() {
	return this->_parent;
}
Object* getRootHelper(Object* obj) {
	if (!obj->getParent()) {
		return obj;
	}
	return getRootHelper(obj->getParent());
}
Object* Object::getRoot() {
	return getRootHelper(this);
}
bool Object::isInScene() {
	return this->_inScene;
}