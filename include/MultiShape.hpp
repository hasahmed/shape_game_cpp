#pragma once
#include <vector>
#include "Object.hpp"
#include "Position.hpp"

namespace shapegame {
	class MultiShape : public Object {
		protected:
		std::vector<Shape*> shapes;
		public:
		MultiShape(Object* controller, std::vector<Shape*>& shapes);
		MultiShape(Position pos);
		virtual void onAdd() override;
		virtual void onKill() override;
		virtual void onRemove() override; //Object
		virtual void setPosition(double x, double y) override;
		// virtual void translate(float x, float y);
	};
}