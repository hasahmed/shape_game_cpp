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
            virtual void onRemove(); //called on removal
            virtual void onKill(); //called as soon as kill is called
            virtual void onKeyPress(Kb::Key key, Input::Action action);
            virtual void onMouseClick(Mouse::Btn btn, Input::Action action);
    };
}
