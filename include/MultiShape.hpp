#pragma once
#include <vector>
#include "Object.hpp"

namespace shapegame {
	class MultiShape : public Object {
		std::vector<Shape*> shapes;
		public:
		MultiShape(Object* controller, std::vector<Shape*>& shapes);
		virtual void onAdd() override;
		virtual void onKill() override;
		virtual void onRemove() override; //Object
		virtual void setPosition(double x, double y) override;
	};
}