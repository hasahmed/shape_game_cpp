#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLHandler.hpp"
#include "Window.hpp"
//#include "main.hpp"

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
#define gl_check_error() _gl_check_error(__FILE__,__LINE__)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
         glfwSetWindowShouldClose(window, true);
    //std::cout << key << ":" << scancode << ":" << action << ":" << mods << std::endl;
}
void check_shader_err(int shader){
    char infoLog[512];
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


void _gl_check_error(const char *file, int line) {
    using namespace std;
    GLenum err (glGetError());
    while(err!=GL_NO_ERROR) {
        string error;
        switch(err) {
            case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
            case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }

        cerr << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<endl;
        err=glGetError();
    }
}

int err = GL_NO_ERROR;

//must enable alpha channel
int main() {
    GLFWwindow* window;
    shapegame::Window w(640, 480, "Hello World!");
    window = w.window_handle;
    std::cout << w.info_string() << std::endl;


    float points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };



    //makeing of shader program
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    //check err
    check_shader_err(vs);
    //check err

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    //check err
    check_shader_err(fs);
    //check err
    GLuint shader_prog = glCreateProgram();
    glAttachShader(shader_prog, fs);
    glAttachShader(shader_prog, vs);
    glLinkProgram(shader_prog);
    //check err
    check_shader_err(fs);
    //check err
    glUseProgram(shader_prog);
    //end making of shader program

    //delete shaders because they are linked into a program, so shader_prog is all we need
    //glDetachShader(shader_prog, fs);
    //glDetachShader(shader_prog, vs);
    glDeleteShader(fs);
    glDeleteShader(vs);
    //end delete shaders


    float color[] = {1.0, 1.0, 0.0, 1.0};




    //vbo
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    GLint uniloc = glGetUniformLocation(shader_prog, "incolor");
    //check_gl_error();
    //glUniform4vf count should be 1 because we are sending in 1 vec4 to the shader
    glUniform4fv(uniloc, 1, color);

    //check_gl_error();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_DYNAMIC_DRAW); //dynamic because it will be modified often and updated often

    //vao
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    //end vao

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    /* Make the window's context current */
    glClearColor(0.0f, 1.0f, 1.0f, 0.5f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glfwSetKeyCallback(window, key_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        points[0] += 0.1;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        //glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_LINE_STRIP, 0, 3);
        //update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
