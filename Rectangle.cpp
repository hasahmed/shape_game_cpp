#include "shapegame"

shapegame::Rectangle::Rectangle(
        float height,
        float width,
        Position pos,
        Color color) : Shape(height, width, ShapeType::Rectangle, pos, color) {}

void shapegame::Rectangle::handleInput(GLFWwindow *w) {
    if (glfwGetKey(w, GLFW_KEY_RIGHT))
        this->move(1, 0);
    if (glfwGetKey(w, GLFW_KEY_LEFT))
        this->move(-1, 0);
    if (glfwGetKey(w, GLFW_KEY_UP))
        this->move(0, -1);
    if (glfwGetKey(w, GLFW_KEY_DOWN))
        this->move(0, 1);
}

void shapegame::Rectangle::update(){
    // this->move(0.3, 1.5);
}