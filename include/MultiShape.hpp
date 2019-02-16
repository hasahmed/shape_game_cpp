#pragma once
#include <vector>
#include <memory>
#include "Position.hpp"
#include "Entity.hpp"

namespace shapegame {
	class MultiShape : public Entity {
		protected:
		std::vector<Object*> shapes;
		std::vector<std::unique_ptr<Object>> unAddedShapes;
		public:
		MultiShape(Object* controller, std::vector<Object*>& shapes);
		MultiShape(Position pos);
		virtual void addShape(Object* shape);
		virtual void addShape(std::unique_ptr<Object> shape);
		virtual void onAdd() override;
		virtual void onKill() override;
		virtual void setPosition(float x, float y) override;
		virtual void setPosition(Point pos) override;
		virtual void setZOrder(int zOrder) override;
		// virtual void translate(float x, float y);
	};
}