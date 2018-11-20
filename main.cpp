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

class Player : public Rectangle {
    public:
    void handleInput(GLFWwindow *w) {
        if (glfwGetKey(w, GLFW_KEY_RIGHT))
            this->move(1, 0);
        if (glfwGetKey(w, GLFW_KEY_LEFT))
            this->move(-1, 0);
        if (glfwGetKey(w, GLFW_KEY_UP))
            this->move(0, -1);
        if (glfwGetKey(w, GLFW_KEY_DOWN))
            this->move(0, 1);
    }
    Player(float height, float width, Position pos, Color color):
        Rectangle(height, width, pos, color) {}
};



int main() {
    shapegame::Game game;
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(game.getWindow()->window_handle, _key_callback);
    Player *const tmp = new Player(240, 240, Position(0, 0), Color::YELLOW);
    Player &tmp2 = *tmp;
    // Rectangle *const tmp = new Rectangle(240, 240, Position(0, 0), Color::YELLOW);
    // Rectangle &tmp2 = *tmp;

    game.scene->addChild(tmp2);
    game.run();
}
