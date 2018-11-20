#include "shapegame"
using namespace shapegame;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main() {

    shapegame::Game game;
    //Your game logic here
    // ...
    // for (int x = 0; x < 480; x++) {
    //     for (int y = 0; y < 480; y++) {
    //     }
    //     if (x >= 240)
    //         break;
    // }
    Rectangle tmp = Rectangle(240, 240, Position(0, 0), Color::YELLOW);
    // tmp.update();
    // tmp.move(200, 0);
    // tmp.update();
    // const auto tmp = Rectangle(240, 240, Position(0, 0), Color::YELLOW);
    game.scene->addChild(tmp);
    // ...
    game.run();
}
