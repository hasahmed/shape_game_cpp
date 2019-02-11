#pragma once
#include "Object.hpp"
#include "Component.hpp"

namespace shapegame {
	class Entity : public Object {
		public:
		std::vector<std::unique_ptr<Component>> compos;
		Entity(Position pos);
		Entity() = default;
		virtual ~Entity();
		virtual void addComponent(Component *compo);
		virtual void addComponent(std::unique_ptr<Component> compo);
	};
}
