#include "shapegame"
using namespace shapegame::Input;
bool Key::down(int key) {
	GLFWwindow *w = Game::inst().getWindow()->window_handle;
	return glfwGetKey(w, key) == GLFW_PRESS;
}