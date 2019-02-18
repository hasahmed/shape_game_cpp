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
            const GLubyte* gl_renderer;
            const GLubyte* gl_version;
            GLFWwindow* window_handle;
        public:
            // GLFWwindow* getWindowHandle();
            std::string info_string();
            Window(int width, int height, std::string window_title);
            GLFWwindow* getWindowHandle() const;
            // static Window* getWindow();

            int getHeight();
            int getWidth();
    };

}
