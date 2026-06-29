#pragma once
#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"
#include "Point.hpp"

namespace shapegame {
	class Entity : public Object {
		friend class Scene;
		private:
			std::vector<std::unique_ptr<Component>> compos;
		public:
			Entity(Point pos);
			Entity() = default;
			virtual ~Entity();
			void addComponent(Component *compo);
			void addComponent(std::unique_ptr<Component> compo);
	};
}
