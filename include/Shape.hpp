#pragma once
#include "Object.hpp"
#include "Drawable.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Globals.hpp"

namespace shapegame {
    class Shape : public Object {
        friend class Scene;
        protected:
            float _height;
            float _width;
            Color _color;
            Shape(float height, float width, ShapeType type, Color color);
            Shape(float height, float width, ShapeType type, Position pos, Color color);
        public:
            ShapeType type;
            float height();
            float width();
    };
}
