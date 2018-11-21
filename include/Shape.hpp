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
            Color _color;
            bool _dirty = false;
        public:
            Shape(float height, float width, ShapeType type, Color color);
            Shape(float height, float width, ShapeType type, Position pos, Color color);
            ShapeType type;
            float height() const;
            float width() const;
            void move(double x, double y);
            void move(Position pos);
            void putAt(Position pos);
            void putAt(double x, double y);
            virtual void update();
            virtual void handleInput(GLFWwindow *w);
            virtual void onAdd();
    };
}
