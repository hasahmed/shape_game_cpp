#pragma once
#include "Position.hpp"
namespace shapegame {
    class GameObject {
        private:
            int x;
            int y;
        public:
            int getY();
            int getX();
            int setX();
            int setY();
            void update();
    };
}
