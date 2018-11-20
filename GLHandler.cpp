#include <iostream>
#include <ctime>
#include <chrono>
#include "shapegame"

int shapegame::GLHandler::_assignableVertexAttribIndex = 0;

int shapegame::GLHandler::getAssignableVertexAttribIndex() {
    // *Learning note* It looks like the vertexattribindex is
    // related to variables in the fragment shader. Because
    // all of our objects utilize the same fragment shader,
    // there is no need to have any number other than 0.?
    // So there previous implementation of consetenty incrementing
    // the _assignableVertexAttribIndex has been removed
    // in favor of just passing out 0. As far as I know that is correct.
    // int nextValid = _assignableVertexAttribIndex++;
    int nextValid = _assignableVertexAttribIndex;
    return nextValid;
}

shapegame::GLHandler::GLHandler(Window *window, Scene &scene) : _scene(scene) {
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
    scene.setShaderProg(this->shader_prog);
    GLCALL(glBindAttribLocation(this->shader_prog, 2, "mouse_vert"));
    //std::cout << this->shader_prog << std::endl;
    GLCALL(glAttachShader(this->shader_prog, fs));
    GLCALL(glAttachShader(this->shader_prog, vs));
    GLCALL(glLinkProgram(this->shader_prog));
    check_shader_err(fs);
    GLCALL(glUseProgram(this->shader_prog));
    //end shader prog

    //delete shader
    GLCALL(glDeleteShader(fs));
    GLCALL(glDeleteShader(vs));
    //end delete shader



    //vbo
    GLCALL(glGenVertexArrays(1, &vao)); //generates vertex attribute array
    GLCALL(glGenBuffers(1, &vbo)); //generates 1 gpu buffer object
    GLCALL(glBindVertexArray(vao)); //binds current buffers to current vao
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo)); //binds vbo to the array buffer portion of gpu memory?
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(square_points), square_points, GL_DYNAMIC_DRAW));
    //dynamic because it will be modified often and updated often


    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
    GLCALL(glBindVertexArray(0)); //also an unbinding

    //input to shader program
    GLint uniloc = glGetUniformLocation(this->shader_prog, "incolor");
    GLCALL(glUniform4fv(uniloc, 1, color));
    uniloc = glGetUniformLocation(this->shader_prog, "screen_res");
    GLCALL(glUniform2f(uniloc, window->width(), window->height()));
    check_shader_err(vs);

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glClearColor(0.0f, 1.0f, 1.0f, 1.0f));


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
    //double second_count = 0;
    while (!glfwWindowShouldClose(this->window_handle)) {
        auto t2 = Clock::now();
        std::chrono::duration<float> elapsed_seconds = t2 - t1;
        glfwGetCursorPos(this->window_handle, &mouse_x, &mouse_y);
        //int mouse_pressed = glfwGetMouseButton(this->window_handle, GLFW_MOUSE_BUTTON_LEFT);
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        _scene.drawAll(this->window_handle);

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
