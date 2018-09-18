#include "shapegame"

shapegame::Game::Game(
                     unsigned int windowWidth,
                     unsigned int windowHeight,
                     std::string windowTitle){

    _window = std::make_unique<Window>(windowWidth, windowHeight, windowTitle);
    scene = std::make_unique<Scene>();
    _glHandler = std::make_unique<GLHandler>(_window.get(), *scene);
    _vertexGenerator = std::make_unique<VertexGenerator>(_window.get());
}

shapegame::Game::Game() : Game(480, 480, "ShapeGame") {}

void shapegame::Game::run() {
    std::cout << _window->info_string() << std::endl;
    _glHandler->run();
}
