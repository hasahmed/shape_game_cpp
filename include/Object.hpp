#pragma once
#include "Scene.hpp"
#include "Input.hpp"
#include "Point.hpp"
#include "Transform.hpp"


namespace shapegame {
	using namespace Input;
    class Object {
			friend class Scene;
			friend class MultiShape;
			friend class RenderPackage;
			private:
				bool canKill = false;
				bool _dirty = false;
				bool _inScene = false;
				Object *_parent = nullptr;
				void setParent(Object *parent);
			protected:
				float height = 0.0f;
				float width = 0.0f;
				Point minXY = Point();
				Point maxXY = Point();
			public:
				std::string name = "Object";
				Point pos;
				Transform transform = Transform();
				Object();
				Object(float x, float y); //should be floats
				Object(Point pos);
				void kill();
				Object* getParent();
				Object* getRoot();
				virtual ~Object();
				virtual void update();
				virtual void onAdd();
				virtual void onRemove(); //called on removal
				virtual void onKill(); //called as soon as kill is called
				virtual void onKeyPress(Kb::Key key, Input::Action action);
				virtual void onMouseClick(Mouse::Btn btn, Input::Action action);
				virtual void setPosition(float x, float y); //shouldn't be virtual
				virtual void setPosition(Point pos); // shouldn't be virtual?
				virtual float getHeight();
				virtual float getWidth();
				void translate(float x, float y);
				void translate(Point xy);
				void rotate(float degrees);
				bool isInScene();
    };
}
