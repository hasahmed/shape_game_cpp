#include <exception>
#include "shapegame.hpp"

using namespace shapegame;

bool shapegame::Game::_isRunning = false;

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
    // this->_window = std::make_unique<NullWindow>();
    this->scene = std::make_unique<Scene>();
    this->_glHandler = std::make_unique<GLHandlerImpl>(_window.get(), *scene);
    // this->_glHandler = std::make_unique<NullRenderer>(*this->scene);
    this->_vertexGenerator = std::make_unique<VertexGenerator>(_window.get());

    Game::_inst = this;
}

void Game::initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) {
	this->_glHandler->initRenderObj(rObj, shape, shaderProg);
}

shapegame::Game::Game() : Game(480, 480, "ShapeGame") {}

void shapegame::Game::run() {
    // std::cout << this->_window->infoString() << std::endl;
		shapegame::Game::_isRunning = true;
    this->_glHandler->run();
}

bool shapegame::Game::isRunning() {
	return shapegame::Game::_isRunning;
}

IWindow const* shapegame::Game::getWindow() {
    return this->_window.get();
}

shapegame::Game& shapegame::Game::inst() {
    if (Game::_inst) {
        return *Game::_inst;
    } else {
        throw std::runtime_error("Instance of game cannot be returned before one was constructed");
    }
}
void Game::draw(RenderPackage &rPack){
	this->_glHandler->draw(rPack);
}
void Game::terminateRenderObj(RenderPackage &rPack) {
	this->_glHandler->terminateRenderObj(rPack);
}