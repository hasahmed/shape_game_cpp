#pragma once
#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"

namespace shapegame {
	class Entity : public Object {
		friend class Scene;
		private:
			std::vector<std::unique_ptr<Component>> compos;
		public:
			Entity(Position pos);
			Entity() = default;
			virtual ~Entity();
			void addComponent(Component *compo);
			void addComponent(std::unique_ptr<Component> compo);
	};
}
