#include "GLHandler.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

//shapegame::GLHandler::GLHandler() {}
shapegame::GLHandler::GLHandler() {

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
    //gl_check_error();


    GLint uniloc = glGetUniformLocation(shader_prog, "incolor");
    glUniform4fv(uniloc, 1, color);
    //gl_check_error();



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
