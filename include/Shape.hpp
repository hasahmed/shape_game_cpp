#pragma once
#include "GameObject.hpp"
#include "Drawable.hpp"

namespace shapegame {
    class Shape : public GameObject, public Drawable {
        public:
            // = 0; is c++ syntax for 'true virtual' meaning the class is
            // abstract and must be derived
            virtual void draw() = 0;
    };
}


