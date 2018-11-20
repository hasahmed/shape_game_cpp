#include "shapegame"
using namespace shapegame;
void error_callback(int error, const char* description)
{
    puts(description);
}
void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // std::cout << key << std::endl;
}


int main() {
    shapegame::Game game;
    glfwSetErrorCallback(error_callback);
    std::cout << game.getWindow()->window_handle << std::endl;
    glfwSetKeyCallback(game.getWindow()->window_handle, _key_callback);
    Rectangle *const tmp = new Rectangle(240, 240, Position(0, 0), Color::YELLOW);
    Rectangle &tmp2 = *tmp;

    game.scene->addChild(tmp2);
    game.run();
}
