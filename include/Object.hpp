#pragma once
#include "Scene.hpp"
#include "Position.hpp"
#include "Input.hpp"
#include "Dirtyable.hpp"
#include "Point.hpp"
#include "RotationInfo.hpp"
namespace shapegame {
	using namespace Input;
    class Object : public Dirtyable {
			friend class Scene;
			friend class Position;
			friend class MultiShape;
			friend class RenderPackage;
			private:
				RotationInfo rotationInfo;
				bool canKill = false;
				bool _dirty = false;
				bool _inScene = false;
				Object *_parent = nullptr;
				Point _nextScale = {};
				Point _scale = {1, 1};
				void setParent(Object *parent);
			protected:
				float height = 0.0f;
				float width = 0.0f;

			public:
				std::string name = "Object";
				Position pos;
				Object();
				Object(double x, double y); //should be floats
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
				// note if multiple operations happen at once, do them in this order
				// translate -> roatate -> scale
				void translate(float x, float y);
				void rotate(float degrees);
				void rotateAround(float degrees, Point origin);
				void rotateAround(float degrees, Object &origin);
				void setRotation(float degrees);
				float getRotation() const;
				float getNextRotation() const;
				RotationInfo& getRotationInfo();
				// void scaleX(float scaleFactor);
				// void scaleY(float scaleFactor);
				// void scale(float scaleFactorX, float scaleFactorY);
				// void scale(Point scaleFactor);
				void setScale(Point scale);
				Point getNextScale() const;
				bool isInScene(); //what? why?
				void setDirty(bool dirty) override; //private?
				bool isDirty() override; //private
    };
}
