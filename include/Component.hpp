#pragma once
#include "Object.hpp"
namespace shapegame {
	class Component {
	public:
		Component();
		virtual ~Component();
		// virtual void translate(Object *ent, float x, float y);
		virtual void update(Object *ent);
	};
}