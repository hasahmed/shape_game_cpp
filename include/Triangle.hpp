#pragma once
#include "Shape.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "shapegl.hpp"
#include "Globals.hpp"

namespace shapegame {
    class Triangle : public Shape {
        private:
            float _angles[3];
        public:
            Triangle(float height, float width, float angle1, float angle2,
                    Position pos, Color color);

            //unneeded constructor overloading
            //Triangle(float height, float width, float angle1, float angle2,
                    //double x, double y, Color color);
            int getNumVerts();
            void update();

    };
}
