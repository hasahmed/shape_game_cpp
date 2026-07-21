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
            void generateMesh(Shape &shape, float *verts);
            VertexGenerator(IWindow *window);
        private:
            static VertexGenerator *_instance;
            IWindow *_window;
            void triangleMesh(Shape &shape, float *verts);
            float horPxStep();
            float vertPxStep();
            float yPxToGl(float coord);
            float xPxToGl(float coord);
            Point pxToGl(float x, float y);
            Point pxToGl(Point coords);
    };
}
