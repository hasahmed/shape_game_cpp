#pragma once
#include <memory>
#include "Window.hpp"
#include "GLHandler.hpp"
#include "Scene.hpp"


namespace shapegame {
    class Game {
        private:
            std::unique_ptr<Window> _window;
            std::unique_ptr<GLHandler> _glHandler;
        public:
            std::unique_ptr<Scene> scene;
            Game(
                unsigned int windowWidth,
                unsigned int windowHeight,
                std::string windowTitle);
            Game();
            void run();
    };
}
