#pragma once
#include <GLFW/glfw3.h>
#include <string>
namespace shapegame {

    class Window {

        public:
            GLFWwindow* window_handle;
            int width;
            int height;
            const GLubyte* renderer;
            const GLubyte* version;
            Window(int width, int height, std::string window_title);
    };

}
