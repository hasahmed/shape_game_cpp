#include <typeinfo>
#include "GLHandler.hpp"
#include <iostream>
#include <ctime>
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <chrono>
#include "Globals.hpp"
#include "FileUtil.hpp"
#include "Window.hpp"

shapegame::GLHandler::GLHandler(Window *window) {
    this->window_handle = window->window_handle;

    //compile and link shaders
    //------------------------------------------------------------------------
    //vert
    std::string _vert_shader = FileUtil::read("shaders/default.vert");
    const char *vertex_shader = _vert_shader.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    check_shader_err(vs);
    //end vert

    //frag
    std::string _frag_shader = FileUtil::read("shaders/default.frag");
    const char *fragment_shader = _frag_shader.c_str();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    check_shader_err(fs);
    //end frag


    //shader prog
    this->shader_prog = glCreateProgram();
    glBindAttribLocation(this->shader_prog, 2, "mouse_vert");
    //std::cout << this->shader_prog << std::endl;
    glAttachShader(this->shader_prog, fs);
    glAttachShader(this->shader_prog, vs);
    glLinkProgram(this->shader_prog);
    check_shader_err(fs);
    glUseProgram(this->shader_prog);
    //end shader prog

    //delete shader
    glDeleteShader(fs);
    glDeleteShader(vs);
    //end delete shader



    //vbo
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

    //input to shader program
    GLint uniloc = glGetUniformLocation(this->shader_prog, "incolor");
    glUniform4fv(uniloc, 1, color);
    uniloc = glGetUniformLocation(this->shader_prog, "screen_res");
    glUniform2f(uniloc, window->width, window->height);
    check_shader_err(vs);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 1.0f, 1.0f, 0.5f);

}
void shapegame::GLHandler::check_shader_err(int shader){
    char infoLog[512];
    int success = 1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void shapegame::GLHandler::run() {
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    double second_count = 0;
    while (!glfwWindowShouldClose(this->window_handle)) {
        auto t2 = Clock::now();
        std::chrono::duration<float> elapsed_seconds = t2 - t1;
        printf("%f\n", elapsed_seconds.count());
        glfwGetCursorPos(this->window_handle, &mouse_x, &mouse_y);
        int mouse_pressed = glfwGetMouseButton(this->window_handle, GLFW_MOUSE_BUTTON_LEFT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);


        //points[0] += 0.01;

        //std::cout << this->shader_prog << std::endl;
        GLuint uniloc = glGetUniformLocation(this->shader_prog, "mouse");
        glUniform3f(uniloc, mouse_x, mouse_y, mouse_pressed);
        auto u_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        uniloc = glGetUniformLocation(this->shader_prog, "u_time");
        glUniform1f(uniloc, elapsed_seconds.count());

        //ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &points[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //gl_check_error();
        //glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //end ebo


        //update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapInterval(1);
        glfwSwapBuffers(this->window_handle);
        //std::cout << elapsed_seconds.count() << std::endl;
        //second_count += elapsed_seconds.count();
        //std::cout << second_count << std::endl;
        //fps++;
        //std::cout << "delta: " << elapsed_seconds.count() << std::endl;
    }

    glfwTerminate();
}
