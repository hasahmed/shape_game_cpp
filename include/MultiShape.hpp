#pragma once
#include <vector>
#include "Shape.hpp"

namespace shapegame {
	class MultiShape : public Shape {
		std::vector<Shape> shapes;
		public:
			virtual void onAdd() override;
			virtual void onKill() override;
			virtual void onRemove() override; //Object
			virtual void translate(double x, double y) override;
			virtual void translate(Position pos) override;
			virtual void setPosition(Position pos) override;
			virtual void setPosition(double x, double y) override;
	};
}