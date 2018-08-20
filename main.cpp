#ifndef __MACH__
#include <glad/glad.h>
#endif
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "GLHandler.hpp"
#include "Window.hpp"
#include "ShaderHandler.hpp"

typedef std::chrono::high_resolution_clock Clock;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main() {

    GLFWwindow* window;
    shapegame::Window w(1140, 480, "Hello World!");
    window = w.window_handle;
    std::cout << w.info_string() << std::endl;
    glfwSetKeyCallback(window, key_callback);
    shapegame::GLHandler gl(window);
    gl.run();
}
