#pragma once
#include "shapegl.hpp"
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
