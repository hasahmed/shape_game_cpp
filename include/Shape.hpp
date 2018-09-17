#pragma once
#include "Object.hpp"
#include "Drawable.hpp"
#include "Color.hpp"
#include "Scene.hpp"

namespace shapegame {
    class Shape : public Object {
        friend class Scene;
        protected:
            Color _color;

        public:
            Shape(Color color);
            Shape(Position pos, Color color);
    };
}
