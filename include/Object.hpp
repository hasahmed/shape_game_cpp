#pragma once
#include "Scene.hpp"
#include "Position.hpp"
namespace shapegame {
    class Object {
        friend class Scene;
        private:
            bool canKill = false;
        public:
            Position pos;
            Object(double x = 0, double y = 0);
            Object(Position pos);
            void kill();
            virtual ~Object();
            virtual void update() = 0;
            virtual void onAdd() = 0;
            virtual void onRemove();
            virtual void onKeyPress(int key, int action) = 0;
    };
}
