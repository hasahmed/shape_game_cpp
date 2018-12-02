#pragma once
#include "Position.hpp"
namespace shapegame {
    class Object {
        public:
            Position pos;
            Object(double x = 0, double y = 0);
            Object(Position pos);
            virtual ~Object();
            virtual void update() = 0;
            virtual void onAdd() = 0;
            virtual void onKeyPress(int key, int action) = 0;
    };
}
