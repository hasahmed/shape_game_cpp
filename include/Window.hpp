#pragma once
#include "shapegl.hpp"
#include <string>
namespace shapegame {

    class Window {
        private:
            Window(){}
            static Window _instance;
            int _width;
            int _height;

        public:
            GLFWwindow* window_handle;
            // GLFWwindow* getWindowHandle();
            const GLubyte* gl_renderer;
            const GLubyte* gl_version;
            std::string info_string();
            Window(int width, int height, std::string window_title);
            // static Window* getWindow();

            int height();
            int width();
    };

}
