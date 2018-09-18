#pragma once
#include "Shape.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include <memory>

namespace shapegame {
    class VertexGenerator {
        friend class Game;
        public:
            static VertexGenerator* instance();
            std::vector<float> generate(Shape &shape);
            VertexGenerator(Window *window);
        private:
            static VertexGenerator *_instance;
            Window *_window;
            std::vector<float> triangleVerts(Shape &shape);
            std::vector<float> rectangleVerts(Shape &shape);
            float getHorizontalPixelStep();
            float getVerticalPixelStep();
    };
}
