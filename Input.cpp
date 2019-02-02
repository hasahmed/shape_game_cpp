#include "shapegame"
using namespace shapegame;
using namespace shapegame::Input;
bool Kb::down(Kb::Key key) {
	GLFWwindow *w = Game::inst().getWindow()->window_handle;
	return glfwGetKey(w, (int)key) == GLFW_PRESS;
}
bool Kb::up(Kb::Key key) {
	return !Kb::down(key);
}

Position Mouse::pos() {
	GLFWwindow *w = Game::inst().getWindow()->window_handle;
	double x = 0;
	double y = 0;
	glfwGetCursorPos(w, &x, &y);
	return Position(x, y);
}