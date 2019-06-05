#pragma once
#include "Object.hpp"
#include "Drawable.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Position.hpp"
#include "Globals.hpp"
#include "Dirtyable.hpp"
#include "Entity.hpp"

namespace shapegame {
    class Shape : public Entity {
        friend class Scene;
        friend class RenderPackage;
        protected:
					float _height; // not needed?
					float _width; //not needed?
        public:
					bool collidable = false; //not needed?
					Color color;
					ShapeType type;
					virtual ~Shape();
					Shape(float height, float width, ShapeType type, Color color);
					Shape(float height, float width, ShapeType type, Position pos, Color color);
					float getHeight() const;
					float getWidth() const;
					virtual void onCollisionStart(Shape &other);
					virtual void onCollisionStop(Shape &other);
					virtual void onColliding(Shape &other);
					bool isColliding(Shape &other);
					virtual void translate(float x, float y);
					virtual void translate(Position pos);
    };
}
// std::ostream& operator<< (std::ostream& stream, const shapegame::Shape& shape);