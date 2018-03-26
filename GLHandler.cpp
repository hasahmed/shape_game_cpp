#include "GLHandler.hpp"
#include <iostream>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <chrono>
#include "Globals.hpp"

//shapegame::GLHandler::GLHandler() {}
shapegame::GLHandler::GLHandler(GLFWwindow *window_handle) {
    this->window_handle = window_handle;

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

    GLint uniloc = glGetUniformLocation(shader_prog, "incolor");
    glUniform4fv(uniloc, 1, color);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 1.0f, 1.0f, 0.5f);

// typedef std::chrono::high_resolution_clock Clock;
//     int fps = 0;
//     double second_count = 0;
//     while (!glfwWindowShouldClose(this->window_handle)) {
//         shapegame::gl_check_error();
//         auto t1 = Clock::now();
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         glBindVertexArray(vao);


//         points[0] += 0.01;

//         //ebo
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//         glBindBuffer(GL_ARRAY_BUFFER, vbo);
//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &points[0]);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//         glBindVertexArray(0);
//         //end ebo


//         //update other events like input handling
        // glfwPollEvents();
        // // put the stuff we've been drawing onto the display
        // glfwSwapInterval(1);
        // glfwSwapBuffers(this->window_handle);
        // auto t2 = Clock::now();
        // std::chrono::duration<double> elapsed_seconds = t2 - t1;
        // second_count += elapsed_seconds.count();
        // //std::cout << second_count << std::endl;
        // fps++;
        // //std::cout << "delta: " << elapsed_seconds.count() << std::endl;
        // if (second_count >= 1.0) {
        //     fps = 0;
        //     second_count = 0;
        // }
        // //std::cout << "delta: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << std::endl;
    // }

    // glfwTerminate();

}

void shapegame::GLHandler::run() {
typedef std::chrono::high_resolution_clock Clock;
    int fps = 0;
    double second_count = 0;
    while (!glfwWindowShouldClose(this->window_handle)) {
        auto t1 = Clock::now();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);


        points[0] += 0.01;


        //ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &points[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //end ebo


        //update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapInterval(1);
        glfwSwapBuffers(this->window_handle);
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
    }

    glfwTerminate();
}
