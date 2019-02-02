#pragma once
#include "Scene.hpp"
#include "Position.hpp"
#include "Input.hpp"
namespace shapegame {
	using namespace Input;
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
            virtual void update();
            virtual void onAdd();
            // when the object is actually removed from the scene
            virtual void onRemove();
            // as soon as kill is called
            virtual void onKill();
            virtual void onKeyPress(Key key, int action);
            // virtual void onKeyPress(int key, int action) = 0;
    };
}
