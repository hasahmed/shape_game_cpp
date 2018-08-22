#pragma once
#ifndef __MACH__
#include <glad/glad.h>
#endif
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include "FileUtil.hpp"

namespace shapegame {
    class GLHandler {
        private:
            GLFWwindow *window_handle;
            GLuint vbo, vao, ebo;

        public:
            float color[4] = {1.0, 1.0, 0.0, 1.0};
            float points[12] = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left
            };
            unsigned int indices[6] = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
            };
            GLuint shader_prog;
            GLHandler(GLFWwindow *window_handle);
            double mouse_x, mouse_y;


            //methods
            void check_shader_err(int shader);
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
            void run();
    };
}
