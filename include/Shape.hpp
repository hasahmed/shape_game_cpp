#pragma once
#include "GameObject.hpp"
#include "Drawable.hpp"
#include "Color.hpp"

namespace shapegame {
    class Shape : GameObject, Drawable {
        private:
            Color _color;
        public:
            // = 0; is c++ syntax for 'true virtual' meaning the class is
            // abstract and must be derived
            virtual void draw() = 0;
            Shape(Color color);
            Shape(int numVerts) : Drawable(numVerts), _color(1.0, 1.0, 1.0, 1.0) {}
    };
}


