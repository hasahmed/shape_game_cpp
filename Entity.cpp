#include "shapegame"

using namespace shapegame;

Entity::Entity(Position pos): Object(pos){}
void Entity::addComponent(Component *compo) {
	this->compos.emplace_back(compo);
}
void Entity::addComponent(std::unique_ptr<Component> compo) {
	this->compos.push_back(std::move(compo));
}
Entity::~Entity(){}