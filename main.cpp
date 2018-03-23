#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "GLHandler.hpp"
#include "Window.hpp"
//#include "main.hpp"

typedef std::chrono::high_resolution_clock Clock;


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
    if (key == GLFW_KEY_1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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




    //window creation
    //------------------------------------------------------------------------
    GLFWwindow* window;
    shapegame::Window w(640, 480, "Hello World!");
    window = w.window_handle;
    std::cout << w.info_string() << std::endl;
    glfwSetKeyCallback(window, key_callback);







    //compile and link shaders
    //------------------------------------------------------------------------
    //vert
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    check_shader_err(vs);
    //end vert

    //frag
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    check_shader_err(fs);
    //end frag


    //shader prog
    GLuint shader_prog = glCreateProgram();
    glAttachShader(shader_prog, fs);
    glAttachShader(shader_prog, vs);
    glLinkProgram(shader_prog);
    check_shader_err(fs);
    glUseProgram(shader_prog);
    //end shader prog

    //delete shader
    glDeleteShader(fs);
    glDeleteShader(vs);
    //end delete shader






    //set up vertext data
    //------------------------------------------------------------------------
    float color[] = {1.0, 1.0, 0.0, 1.0};
    //float points[] = {
        //-0.5f, -0.5f, 0.0f, // left
        //0.5f, -0.5f, 0.0f, // right
        //0.0f,  0.5f, 0.0f  // top
    //};

    float points[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };



    //vbo
    GLuint vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW); //dynamic because it will be modified often and updated often

    //-----------------------------------------ebo
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //<-----------------------------------------ebo


    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //this is actually an unbinding
    glBindVertexArray(0); //also an unbinding
    gl_check_error();


    GLint uniloc = glGetUniformLocation(shader_prog, "incolor");
    glUniform4fv(uniloc, 1, color);
    gl_check_error();



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gl_check_error();

    glClearColor(0.0f, 1.0f, 1.0f, 0.5f);
    /* Loop until the user closes the window */
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int fps = 0;
    double second_count = 0;
    while (!glfwWindowShouldClose(window)) {
        auto t1 = Clock::now();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);


        points[0] += 0.01;

        gl_check_error();

        //ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &points[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //end ebo



        //non ebo
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_DYNAMIC_DRAW);

        //update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        auto t2 = Clock::now();
        std::chrono::duration<double> elapsed_seconds = t2 - t1;
        second_count += elapsed_seconds.count();
        //std::cout << second_count << std::endl;
        fps++;
        //std::cout << "delta: " << elapsed_seconds.count() << std::endl;
        if (second_count >= 1.0) {
            fps = 0;
            second_count = 0;
        }
        //std::cout << "delta: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << std::endl;
    }

    glfwTerminate();
    return 0;
}
