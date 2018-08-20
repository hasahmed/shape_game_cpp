#pragma once
#ifndef __MACH__
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <string>
namespace shapegame {

    class Window {
        private:
            Window(){}

        public:
            GLFWwindow* window_handle;
            int width;
            int height;
            const GLubyte* gl_renderer;
            const GLubyte* gl_version;
            std::string info_string();
            Window(int width, int height, std::string window_title);
    };

}
