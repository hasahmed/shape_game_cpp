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
            Point second; // second point of the triangle
            Point third; // third
            Position collisionPosition;
            Triangle(Position first, Point second, Point third);
            Triangle(Position first, Point second, Point third, Color color);
            int getNumVerts();
            void setFirst(Position first);
            void setSecond(Point second);
            void setThird(Point third) {
                this->third = third;
                this->_dirty = true;
            }
            void update() override;
            void onAdd() override;
            void onKeyPress(int key, int action) override;
            void translate(double x, double y) override;
            void translate(Position pos) override;
            void setPosition(Position pos) override;
            void setPosition(double x, double y) override;
    };
}
