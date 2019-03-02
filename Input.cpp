#include "shapegame"
using namespace shapegame;
using namespace shapegame::Input;
bool Kb::down(Kb::Key key) {
	// GLFWwindow *w = Game::inst().getWindow()->getWindowHandle();
	// return glfwGetKey(w, (int)key) == GLFW_PRESS;
	return false;
}
bool Kb::up(Kb::Key key) {
	return false;
	// return !Kb::down(key);
}

Position Mouse::pos() {
	// GLFWwindow *w = Game::inst().getWindow()->getWindowHandle();
	// double x = 0;
	// double y = 0;
	// glfwGetCursorPos(w, &x, &y);
	return Position();
}