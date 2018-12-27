#pragma once
#include "Shape.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Point.hpp"
#include <memory>

namespace shapegame {
    class VertexGenerator {
        friend class Game;
        public:
            static VertexGenerator* instance();
            std::vector<float> generate(const Shape &shape);
            VertexGenerator(Window *window);
        private:
            static VertexGenerator *_instance;
            Window *_window;
            std::vector<float> triangleVerts(const Shape &shape);
            std::vector<float> rectangleVerts(const Shape &shape);
            std::vector<float> circleVerts(const Shape &shape);
            float getHorizontalPixelStep();
            float getVerticalPixelStep();
            float pxToGl(float coord);
            Point pxToGl(Point coords);
    };
}
