#include "shapegame"
using namespace shapegame::Input;
bool Kb::down(Kb::Key key) {
	GLFWwindow *w = Game::inst().getWindow()->window_handle;
	return glfwGetKey(w, (int)key) == GLFW_PRESS;
}
bool Kb::up(Kb::Key key) {
	return !Kb::down(key);
}