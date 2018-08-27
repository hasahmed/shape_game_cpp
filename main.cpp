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

    //GLFWwindow* window;
    shapegame::Window window(1140, 480, "Hello World!");
    //window = w.window_handle;
    std::cout << window.info_string() << std::endl;
    glfwSetKeyCallback(window.window_handle, key_callback);
    shapegame::GLHandler gl(&window);
    gl.run();
}
