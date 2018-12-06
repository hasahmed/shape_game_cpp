#include <exception>
#include "shapegame"

using namespace shapegame;

Game* Game::_inst = nullptr;

shapegame::Game::Game(
    unsigned int windowWidth,
    unsigned int windowHeight,
    std::string windowTitle
){
    if (Game::_inst) {
        throw std::runtime_error("Game can only be constructed once");
    }
    this->_window = std::make_unique<Window>(windowWidth, windowHeight, windowTitle);
    this->scene = std::make_unique<Scene>();
    this->_glHandler = std::make_unique<GLHandler>(_window.get(), *scene);
    this->_vertexGenerator = std::make_unique<VertexGenerator>(_window.get());

    Game::_inst = this;
}
shapegame::Game::Game() : Game(480, 480, "ShapeGame") {}

void shapegame::Game::run() {
    // std::cout << this->_window->info_string() << std::endl;
    this->_glHandler->run();
}

shapegame::Window const* shapegame::Game::getWindow() {
    return this->_window.get();
}

shapegame::Game& shapegame::Game::inst() {
    if (Game::_inst) {
        return *Game::_inst;
    } else {
        throw std::runtime_error("Instance of game cannot be returned before one was constructed");
    }
}