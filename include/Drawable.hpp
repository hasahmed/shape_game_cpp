#pragma once
namespace shapegame {
    class Drawable {
        public:
            // = 0; is c++ syntax for 'true virtual' meaning the class is
            // abstract and must be derived
            virtual void draw() = 0;
    };
}

