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
			friend class MultiShape;
			private:
				bool canKill = false;
				bool _dirty = false;
				bool _inScene = false;
				Object *_parent = nullptr;
				void setParent(Object *parent);
				int zOrder = 0;
			public:
				std::string name = "Object";
				Position pos;
				Object();
				Object(double x, double y);
				Object(Point pos);
				void kill();
				Object* getParent();
				virtual ~Object();
				virtual void update();
				virtual void onAdd();
				virtual void onRemove(); //called on removal
				virtual void onKill(); //called as soon as kill is called
				virtual void onKeyPress(Kb::Key key, Input::Action action);
				virtual void onMouseClick(Mouse::Btn btn, Input::Action action);
				virtual void setPosition(float x, float y);
				virtual void setPosition(Point pos);
				virtual void translate(float x, float y);
				virtual int getZOrder();
				bool isInScene();
				void setDirty(bool dirty) override;
				bool isDirty() override;
    };
}
