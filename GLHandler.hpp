#pragma once
#include <GLFW/glfw3.h>
namespace shapegame {
    class GLHandler {
        private:
            GLuint shader_prog;
            GLFWwindow *window;
        public:
            GLHandler();
            //void _check_gl_error(const char *file, int line);
    };
}
