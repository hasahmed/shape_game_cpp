#pragma once
namespace shapegame {
    class Position {
        private:
            float _x;
            float _y;
        public:
            Position(float x, float y);
            float x();
            float y();
    };
}
