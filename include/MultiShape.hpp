#pragma once
#include <vector>
#include "Object.hpp"
#include "Position.hpp"

namespace shapegame {
	class MultiShape : public Object {
		protected:
		std::vector<Object*> shapes;
		public:
		MultiShape(Object* controller, std::vector<Object*>& shapes);
		MultiShape(Position pos);
		virtual void addShape(Object* shape);
		virtual void onAdd() override;
		virtual void onKill() override;
		virtual void setPosition(float x, float y) override;
		virtual void setPosition(Point pos) override;
		virtual void setZOrder(int zOrder) override;
		// virtual void translate(float x, float y);
	};
}