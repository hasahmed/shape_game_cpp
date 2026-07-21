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
			private:
				Point first;
				Point second;
				Point third; 
			public:
				using Shape::setPosition;
				// pos inherited from Object
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
