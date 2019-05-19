#pragma once
#include <iostream>
#include "shapegl.hpp"
#include "IWindow.hpp"
#include "Scene.hpp"
#include "Color.hpp"
#include "GLHandler.hpp"
#include "RenderPackage.hpp"
#include "GLRenderObject.hpp"

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
            GLHandlerImpl(IWindow *window, Scene &scene);
            //methods
            void check_shader_err(int shader);
            void setClearColor(Color& color) override;
						void terminateRenderObj(RenderPackage &rPack) override;
						void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) override;
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
						void draw(RenderPackage &rPack) override;
            void run() override;
    };
}
