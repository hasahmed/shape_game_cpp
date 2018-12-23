#pragma once
#include <unordered_set>
#include "CollisionList.hpp"
#include "ShapePair.hpp"
#include "Shape.hpp"
namespace shapegame {
	class SimpleCollision : public CollisionList {
	private:
		std::vector<ShapePair> findContaining(Shape *shape);
	public:
		std::unordered_set<Shape*> shapeStore;
		std::unordered_set<ShapePair> currentlyColliding_;
		SimpleCollision();
		void add(Shape* shape) override;
		void remove(Shape* shape) override;
		void clear() override;
		void check() override;
	};
}