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
        private:
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
            bool isColliding(Shape &other);
            void translate(double x, double y);
            void translate(Position pos);
            void setPosition(Position pos);
            void setPosition(double x, double y);
    };
}
