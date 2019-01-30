#include "shapegame"
using namespace shapegame::Input;
bool KeyCheck::down(Key key) {
	GLFWwindow *w = Game::inst().getWindow()->window_handle;
	return glfwGetKey(w, (int)key) == GLFW_PRESS;
}