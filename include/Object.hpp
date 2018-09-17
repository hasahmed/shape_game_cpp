#pragma once
#include "Position.hpp"
namespace shapegame {
    class Object {
        protected:
            Position pos;
        public:
            Object(double x, double y);
            Object(Position pos);
    };
}
