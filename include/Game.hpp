#pragma once
#include <memory>
#include "Window.hpp"
#include "GLHandler.hpp"
#include "Scene.hpp"
#include "VertexGenerator.hpp"


namespace shapegame {
    class Game {
        private:
            std::unique_ptr<Window> _window;
            std::unique_ptr<GLHandler> _glHandler;
            std::unique_ptr<VertexGenerator> _vertexGenerator;

        public:
            std::unique_ptr<Scene> scene;
            Window const* getWindow();
            Game(
                unsigned int windowWidth,
                unsigned int windowHeight,
                std::string windowTitle
                );
            Game();
            void run();
    };
}
