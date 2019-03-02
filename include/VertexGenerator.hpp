#pragma once
#include "Shape.hpp"
#include "Game.hpp"
#include "IWindow.hpp"
#include "Point.hpp"
#include <memory>

namespace shapegame {
    class VertexGenerator {
        friend class Game;
        public:
            static VertexGenerator* instance();
            std::vector<float> generate(const Shape &shape);
            VertexGenerator(IWindow *window);
        private:
            static VertexGenerator *_instance;
            IWindow *_window;
            std::vector<float> triangleVerts(const Shape &shape);
            std::vector<float> rectangleVerts(const Shape &shape);
            std::vector<float> circleVerts(const Shape &shape);
            float horPxStep();
            float vertPxStep();
            float yPxToGl(float coord);
            float xPxToGl(float coord);
            Point pxToGl(float x, float y);
            Point pxToGl(Point coords);
    };
}
