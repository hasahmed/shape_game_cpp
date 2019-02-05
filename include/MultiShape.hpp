#pragma once
#include <vector>
#include "Shape.hpp"

namespace shapegame {
	class MultiShape : public Shape {
		std::vector<Shape> shapes;
		public:
		MultiShape(Shape& mainShape, std::vector<Shape*>& shapes);
		void onAdd() override;
		void onKill() override;
		void onRemove() override; //Object
		void setPosition(double x, double y) override;
	};
}