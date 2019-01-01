#pragma once
#include <iostream>
#include "shapegl.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Color.hpp"

namespace shapegame {
    class GLHandler {
        private:
            GLFWwindow *window_handle;
            GLuint vbo, vao;
            Scene &_scene;
            static int _assignableVertexAttribIndex;
            Color _clearColor;
        public:
            float color[4] = {1.0, 1.0, 0.0, 1.0}; // what is this color for?

            // float square_points[9] = { //this actually is a triangle
            //     0.0f, 0.5, 0.0f,
            //     0.5f,  -0.5f, 0.0f,
            //     -0.5f, -0.5f, 0.0f
            // };
            //float square_points[18] = {
                ////right side triangle
                //0.5f,  0.5f, 0.0f,  // top right
                //-0.5f, -0.5f, 0.0f,  // bottom left
                //0.5f, -0.5f, 0.0f,  // bottom right

                //0.5f,  0.5f, 0.0f,  // top right
                //-0.5f, -0.5f, 0.0f,  // bottom left
                //-0.5f,  0.5f, 0.0f   // top left
            //};

            // float line_points[6] = {
            //     -0.9, 0.9, 0.0, //top left
            //     0.5, -0.5, 0.0
            // };
            GLuint shader_prog;
            GLHandler(Window *window, Scene &scene);
            double mouse_x, mouse_y;
            static int getAssignableVertexAttribIndex();


            //methods
            void check_shader_err(int shader);
            void setClearColor(Color& color);
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
            void run();
    };
}
