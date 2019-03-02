#include "shapegame"

using namespace shapegame;

int NullWindow::getHeight() {
	return 500;
}
GLFWwindow* NullWindow::getWindowHandle() const {
	return nullptr;
}

int NullWindow::getWidth() {
	return 500;
}