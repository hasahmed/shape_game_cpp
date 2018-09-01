#include "shapegame"

shapegame::Game::Game() {
    _window = std::make_unique<Window>(480, 480, "Shape Game");
    _glHandler = std::make_unique<GLHandler>(_window.get());
}
