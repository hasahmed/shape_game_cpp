#include "shapegame.hpp"

using namespace shapegame;

GLFWwindow* Window::getWindowHandle() const {
	return this->windowHandle;
}

shapegame::Window::Window(int width, int height, std::string window_title) {

    if (!glfwInit())
        throw std::runtime_error("glfw failed to initilize");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); //anti-aliasing


    /* Create a windowed mode window and its OpenGL context */
    this->_width = width;
    this->_height = height;
    this->windowHandle = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!this->windowHandle) {
        glfwTerminate();
        throw std::runtime_error("glfw failed to create window");
    }
    glfwMakeContextCurrent(this->windowHandle);
#ifndef __MACH__
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif
    this->gl_renderer = glGetString(GL_RENDERER); // get renderer string
    this->gl_version = glGetString(GL_VERSION); // version as a string


    glfwSetKeyCallback(this->windowHandle, Scene::keyCallback);
		glfwSetMouseButtonCallback(this->windowHandle, Scene::mouseBtnCallback);
}



std::string shapegame::Window::infoString() {
    std::string render_str((char*)(this->gl_renderer));
    std::string version_str((char*)(this->gl_version));
    return "Renderer: " + render_str + "\n" + "OpenGL version supported: " + version_str;
}

int shapegame::Window::getHeight() {
    return _height;
}
int shapegame::Window::getWidth() {
    return _width;
}