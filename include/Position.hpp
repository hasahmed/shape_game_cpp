#pragma once
namespace shapegame {
    class Position {
        private:
            float _x;
            float _y;
        public:
            Position();
            Position(float x, float y);
            float getX() const;
            float getY() const;
            void setX(const double x);
            void setY(const double y);
    };
}