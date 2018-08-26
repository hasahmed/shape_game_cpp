#pragma once
#include <iostream>
#include "shapegame"

namespace shapegame {
    class GLHandler {
        private:
            GLFWwindow *window_handle;
            GLuint vbo, vao;

        public:
            float color[4] = {1.0, 1.0, 0.0, 1.0};
            float square_points[18] = {
                //right side triangle
                0.5f,  0.5f, 0.0f,  // top right
                -0.5f, -0.5f, 0.0f,  // bottom left
                0.5f, -0.5f, 0.0f  // bottom right

                //0.5f,  0.5f, 0.0f,  // top right
                //-0.5f, -0.5f, 0.0f,  // bottom left
                //-0.5f,  0.5f, 0.0f   // top left
            };

            float line_points[6] = {
                -0.9, 0.9, 0.0, //top left
                0.5, -0.5, 0.0
            };
            GLuint shader_prog;
            GLHandler(Window *window);
            double mouse_x, mouse_y;


            //methods
            void check_shader_err(int shader);
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
            void run();
    };
}
