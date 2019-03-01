#pragma once
#include <iostream>
#include "shapegl.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Color.hpp"
#include "GLHandler.hpp"

namespace shapegame {
    class GLHandlerImpl : public GLHandler {
        private:
            GLFWwindow *windowHandle;
            GLuint vbo, vao;
            Scene &_scene;
            static int _assignableVertexAttribIndex;
            Color _clearColor;
        public:

            GLuint shader_prog;
            GLHandlerImpl(Window *window, Scene &scene);
            //methods
            void check_shader_err(int shader);
            void setClearColor(Color& color) override;
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
            void run() override;
    };
}
