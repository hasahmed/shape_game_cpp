#pragma once
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
