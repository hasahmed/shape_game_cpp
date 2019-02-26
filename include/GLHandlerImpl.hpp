#pragma once
#include <iostream>
#include "shapegl.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Color.hpp"

namespace shapegame {
    class GLHandlerImpl {
        private:
            GLFWwindow *windowHandle;
            GLuint vbo, vao;
            Scene &_scene;
            static int _assignableVertexAttribIndex;
            Color _clearColor;
        public:
            float color[4] = {1.0, 1.0, 0.0, 1.0}; // what is this color for?

            GLuint shader_prog;
            GLHandlerImpl(Window *window, Scene &scene);
            double mouse_x, mouse_y;
            //methods
            void check_shader_err(int shader);
            void setClearColor(Color& color);
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
            void run();
    };
}
