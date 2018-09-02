#include "shapegame"
shapegame::Window* shapegame::Window::getWindow(){
    return NULL;
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
    this->width = width;
    this->height = height;
    this->window_handle = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!window_handle) {
        glfwTerminate();
        throw std::runtime_error("glfw failed to create window");
    }
    glfwMakeContextCurrent(window_handle);
#ifndef __MACH__
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif
    this->gl_renderer = glGetString(GL_RENDERER); // get renderer string
    this->gl_version = glGetString(GL_VERSION); // version as a string
}
std::string shapegame::Window::info_string() {
    std::string render_str((char*)(this->gl_renderer));
    std::string version_str((char*)(this->gl_version));
    return "Renderer: " + render_str + "\n" + "OpenGL version supported: " + version_str;
}
