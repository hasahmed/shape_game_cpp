#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "shapegame"


using namespace shapegame;

int shapegame::GLHandlerImpl::_assignableVertexAttribIndex = 0;



void GLHandlerImpl::setClearColor(Color& color) {
    this->_clearColor = color;
    GLCALL(glClearColor(
        this->_clearColor.r,
        this->_clearColor.g,
        this->_clearColor.b,
        this->_clearColor.a
    ));
}

shapegame::GLHandlerImpl::GLHandlerImpl(Window *window, Scene &scene) :
    _scene(scene),
    _clearColor(Color::BLACK)
{
    this->windowHandle = window->getWindowHandle();

    //compile and link shaders
    //------------------------------------------------------------------------
    //vert
    std::string _vert_shader = FileUtil::read("shaders/default.vert");
    const char *vertex_shader = _vert_shader.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLCALL(glShaderSource(vs, 1, &vertex_shader, NULL));
    GLCALL(glCompileShader(vs));
    check_shader_err(vs);
    //end vert

    //frag
    std::string _frag_shader = FileUtil::read("shaders/default.frag");
    const char *fragment_shader = _frag_shader.c_str();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLCALL(glShaderSource(fs, 1, &fragment_shader, NULL));
    GLCALL(glCompileShader(fs));
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
    // GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(square_points), square_points, GL_DYNAMIC_DRAW));
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
    GLCALL(glUniform2f(uniloc, window->getWidth(), window->getHeight()));
    check_shader_err(vs);


    // other gl settings

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glClearColor(
        this->_clearColor.r,
        this->_clearColor.g,
        this->_clearColor.b,
        this->_clearColor.a
    ));


// uncomment if back culling is desired
    // GLCALL(glCullFace(GL_BACK));
    // GLCALL(glEnable(GL_CULL_FACE));
		GLCALL(glDepthFunc(GL_NEVER));


}
void shapegame::GLHandlerImpl::check_shader_err(int shader){
    char infoLog[512];
    int success = 1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void shapegame::GLHandlerImpl::run() {
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    while (!glfwWindowShouldClose(this->windowHandle)) {
        auto t2 = Clock::now();
        std::chrono::duration<double> elapsed_seconds = t2 - t1;
        glfwGetCursorPos(this->windowHandle, &mouse_x, &mouse_y);
        this->setClearColor(this->_scene._bgColor);
        //int mouse_pressed = glfwGetMouseButton(this->windowHandle, GLFW_MOUSE_BUTTON_LEFT);
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        _scene.updateChildren();
        _scene.drawChildren(this->windowHandle);
				_scene.killQueued();

				// std::cout << "\r";
				// std::cout << std::flush;
				// std::cout << "drawChildren:" << _scene.drawVect.size() << std::endl;
				// std::cout << "\rdrawChildren:" << _scene.drawVect.size();
				// std::cout << "\rsceneChildren:" << _scene.sceneChildren.size();

        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapInterval(1);
        glfwSwapBuffers(this->windowHandle);
        std::chrono::duration<double> frameLength = Clock::now() - t2;
				G::dt = frameLength.count();
				G::fps = 1.0f / G::dt;
    }

    glfwTerminate();
}
