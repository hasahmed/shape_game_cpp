#pragma once
#include "Object.hpp"
#include "Drawable.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Position.hpp"
#include "Globals.hpp"

namespace shapegame {
    class Shape : public Object {
        friend class Scene;
        friend class RenderPackage;
        protected:
            float _height;
            float _width;
            bool _dirty = false;
        public:
            bool collidable = false;
            Color color;
            ShapeType type;

            ~Shape(){
                // std::cout << "deleted: Shape" << std::endl;
            }
            Shape(float height, float width, ShapeType type, Color color);
            Shape(float height, float width, ShapeType type, Position pos, Color color);
            float getHeight() const;
            float getWidth() const;
            virtual void onCollisionStart(Shape &other);
            virtual void onCollisionStop(Shape &other);
            virtual void onColliding(Shape &other);
            bool isColliding(Shape &other);
            virtual void translate(double x, double y);
            virtual void translate(Position pos);
            virtual void setPosition(Position pos);
            virtual void setPosition(double x, double y);
    };
}