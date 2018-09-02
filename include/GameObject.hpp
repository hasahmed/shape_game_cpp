#pragma once
namespace shapegame {
    class GameObject {
        public:
            int getY();
            int getX();
            int setX();
            int setY();
            virtual void update();
    };
}
