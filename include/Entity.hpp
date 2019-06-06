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
		void addComponent(Component *compo);
		void addComponent(std::unique_ptr<Component> compo);
	};
}
