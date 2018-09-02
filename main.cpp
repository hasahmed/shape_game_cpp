#include "shapegame"

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
    game.scene->addChild(shapegame::GameObject());


    // ...
    game.run();
}
