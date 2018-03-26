#pragma once
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
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
            const char *vertex_shader =
                "#version 410 core\n"
                "in vec3 vp;"
                "void main() {"
                //"  gl_Position = vec4(vp, 1.0);"
                "  gl_Position.xyz = vp;"
                "  gl_Position.w = 1.0;"
                "}";
            const char *fragment_shader =
                "#version 410 core\n"
                "out vec4 frag_color;"
                "uniform vec4 incolor;"
                "void main() {"
                "frag_color = incolor;"
                "}";
            GLuint shader_prog;
            GLHandler(GLFWwindow *window_handle);
            void check_shader_err(int shader){
                char infoLog[512];
                int success;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(shader, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
                }
            }
            //void _check_gl_error(const char *file, int line);

            void run();
    };
}
