#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "shapegl.hpp"
#include "Globals.hpp"
#include "Point.hpp"


namespace shapegame {
	class VertexGenerator;
    class Triangle : public Shape {
			friend class VertexGenerator;
				protected:
				virtual bool recalculateSize() override;
        public:
				using Shape::setPosition;
				// pos inherited from Object
				Point second; // should be private?
				Point third; // should be private?
				Position collisionPosition;
				virtual ~Triangle();
				Triangle();
				Triangle(Position first, Point second, Point third);
				Triangle(Position first, Point second, Point third, Color color);
				virtual void setPosition(float x, float y) override;
    };
}
