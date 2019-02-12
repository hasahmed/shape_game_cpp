#pragma once
// #include "Object.hpp"
namespace shapegame {
	class Entity;
	class Component {
	public:
		virtual ~Component();
		// virtual void translate(Object *ent, float x, float y);
		virtual void update(Entity *ent);
	};
}