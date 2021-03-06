#include "shapegame.hpp"

using namespace shapegame;
using namespace shapegame::Input;

DebugKeyHandler::DebugKeyHandler() {
	this->name = "DebugKeyHandler";
}

void DebugKeyHandler::onKeyPress(Kb::Key key, Input::Action action) {
	if (action != Action::DOWN) return; // skip up actions
	if (key == Kb::Key::ESCAPE)
		glfwSetWindowShouldClose(Game::inst().getWindow()->getWindowHandle(), true);
	if (key == Kb::Key::N1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == Kb::Key::N2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}