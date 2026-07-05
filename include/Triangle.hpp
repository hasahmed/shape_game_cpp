#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "shapegl.hpp"
#include "Globals.hpp"
#include "Point.hpp"


namespace shapegame {
	class VertexGenerator;
    class Triangle : public Shape {
			friend class VertexGenerator;
        public:
				using Shape::setPosition;
				// pos inherited from Object
				Point second; // should be private?
				Point third; // should be private?
				Point collisionPosition;
				Point getCenter();
				Point getOrigin();
				virtual ~Triangle();
				Triangle();
				Triangle(Point first, Point second, Point third);
				Triangle(Point first, Point second, Point third, Color color);
				virtual void setPosition(float x, float y) override;
    };
}
