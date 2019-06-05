#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "shapegl.hpp"
#include "Globals.hpp"
#include "Point.hpp"

namespace shapegame {
    class Triangle : public Shape {
        public:
				using Shape::setPosition;
				Point second; // second point of the triangle
				Point third; // third
				Position collisionPosition;
				virtual ~Triangle();
				Triangle();
				Triangle(Position first, Point second, Point third);
				Triangle(Position first, Point second, Point third, Color color);
				// int getNumVerts();
				// void translate(float x, float y) override;
				// void translate(Position pos) override;
				// void setPosition(Position pos);
				virtual void setPosition(float x, float y) override;
    };
}
