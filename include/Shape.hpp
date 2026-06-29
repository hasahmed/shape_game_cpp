#pragma once
#include "Object.hpp"
#include "Drawable.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Globals.hpp"
#include "Entity.hpp"

namespace shapegame {
    class Shape : public Entity {
        friend class Scene;
        public:
					bool collidable = false; //not needed?
					Color color;
					ShapeType type;
					virtual ~Shape();
					Shape(float height, float width, ShapeType type, Color color);
					Shape(float height, float width, ShapeType type, Point pos, Color color);
					// float getHeight() const;
					// float getWidth() const;
					virtual void onCollisionStart(Shape &other);
					virtual void onCollisionStop(Shape &other);
					virtual void onColliding(Shape &other);
					bool isColliding(Shape &other);
					virtual void translate(float x, float y);
					virtual void translate(Point pos);
    };
}
// std::ostream& operator<< (std::ostream& stream, const shapegame::Shape& shape);