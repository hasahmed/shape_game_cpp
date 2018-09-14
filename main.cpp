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
    //shapegame::GameObject x;
    auto x = shapegame::Triangle(10, 10, 10, 10, Color::PURPLE);
    auto y = shapegame::Triangle(10, 10, 10, 10, Color::YELLOW);

    y._verts[0] = -1.0;
    y._verts[1] = 1.0;
    y._verts[2] = 0.0;

    y._verts[3] = 0.9;
    y._verts[4] = 1.0;
    y._verts[5] = 0.0;

    y._verts[6] = -1.0;
    y._verts[7] = -0.9;
    y._verts[8] = 0.0;
    game.scene->addChild(x);
    game.scene->addChild(y);
    // ...
    game.run();
}
