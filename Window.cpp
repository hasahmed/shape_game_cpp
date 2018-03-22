#include "Window.hpp"
#include <stdexcept>
shapegame::Window::Window(int width, int height, std::string window_title) {

    if (!glfwInit())
        throw std::runtime_error("glfw failed to initilize");
    //uncomment these lines if on Apple OS X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    this->width = width;
    this->height = height;
    this->window_handle = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!window_handle) {
        glfwTerminate();
        throw std::runtime_error("glfw failed to create window");
    }
    glfwMakeContextCurrent(window_handle);
    this->renderer = glGetString(GL_RENDERER); // get renderer string
    this->version = glGetString(GL_VERSION); // version as a string
}
