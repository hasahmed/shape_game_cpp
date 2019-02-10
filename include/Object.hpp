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
			friend class Position;
			private:
				bool canKill = false;
				bool _dirty = false;
			protected:
				// int zOrder = 0;
			public:
				int zOrder = 0;
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
				virtual void setPosition(double x, double y);
				virtual void translate(float x, float y);
				void setDirty(bool dirty) override;
				bool isDirty() override;
    };
}
