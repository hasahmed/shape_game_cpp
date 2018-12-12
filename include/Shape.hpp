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
            ~Shape(){
                // std::cout << "deleted: Shape" << std::endl;
            }
            Color color;
            Shape(float height, float width, ShapeType type, Color color);
            Shape(float height, float width, ShapeType type, Position pos, Color color);
            ShapeType type;
            float height() const;
            float width() const;
            void translate(double x, double y);
            void translate(Position pos);
            void setPosition(Position pos);
            void setPosition(double x, double y);
    };
}
