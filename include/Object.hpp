#pragma once
#include "Position.hpp"
namespace shapegame {
    class Object {
        public:
            Position pos;
            Object(double x, double y);
            Object(Position pos);
    };
}
