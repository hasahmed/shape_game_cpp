#pragma once
#include "Scene.hpp"
#include "Position.hpp"
#include "Input.hpp"
#include "Dirtyable.hpp"
#include "Point.hpp"
namespace shapegame {
	using namespace Input;
    class Object : public Dirtyable {
        friend class Scene;
        private:
            bool canKill = false;
						bool _dirty = false;
        public:
            Position pos;
            Object();
            Object(double x, double y);
            Object(Point pos);
            void kill();
            virtual ~Object();
            virtual void update();
            virtual void onAdd();
            virtual void onRemove(); //called on removal
            virtual void onKill(); //called as soon as kill is called
            virtual void onKeyPress(Kb::Key key, Input::Action action);
            virtual void onMouseClick(Mouse::Btn btn, Input::Action action);
						void setDirty(bool dirty) override;
						bool isDirty() override;
    };
}
