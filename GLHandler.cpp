#include "GLHandler.hpp"
#include <iostream>

shapegame::GLHandler::GLHandler() {}
//shapegame::GLHandler::GLHandler() {
    //const char *vertex_shader =
        //"#version 410\n"
        //"in vec3 vp;"
        //"void main() {"
        //"gl_Position = vec4(vp, 1.0);"
        //"}";
    //const char *fragment_shader =
        //"#version 410\n"
        //"out vec4 frag_color;"
        //"uniform vec4 incolor;"
        //"void main() {"
        //"frag_color = incolor;"
        //"}";
    //GLFWwindow* window;
    //[> Initialize the library <]
    //if (!glfwInit())
        //return -1;
    ////uncomment these lines if on Apple OS X
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //[> Create a windowed mode window and its OpenGL context <]
    //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    //if (!window) {
        //glfwTerminate();
        //return -1;
    //}
    //glfwMakeContextCurrent(window);
    //const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    //const GLubyte* version = glGetString(GL_VERSION); // version as a string
    //printf("Renderer: %s\n", renderer);
    //printf("OpenGL version supported %s\n", version);


    //float points[] = {
        //0.0f,  0.5f,  0.0f,
        //0.5f, -0.5f,  0.0f,
        //-0.5f, -0.5f,  0.0f
    //};



    ////makeing of shader program
    //GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vs, 1, &vertex_shader, NULL);
    //glCompileShader(vs);
    //GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fs, 1, &fragment_shader, NULL);
    //glCompileShader(fs);
    //GLuint shader_prog = glCreateProgram();
    //glAttachShader(shader_prog, fs);
    //glAttachShader(shader_prog, vs);
    //glLinkProgram(shader_prog);
    //glUseProgram(shader_prog);
    ////end making of shader program

    ////delte shaders. For why?
    //glDetachShader(shader_prog, fs);
    //glDetachShader(shader_prog, vs);
    //glDeleteShader(fs);
    //glDeleteShader(vs);
    ////check_gl_error();
    ////end delete shaders


    //float color[] = {1.0, 1.0, 0.0, 0.0};

    //std::cout << typeid(color).name() << std::endl;



    ////vao
    //GLuint vao = 0;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);
    //glEnableVertexAttribArray(0);
    ////end vao


    //GLuint vbo = 0;
    //glGenBuffers(1, &vbo);
    //GLint uniloc = glGetUniformLocation(shader_prog, "incolor");
    ////check_gl_error();
    ////glUniform4vf count should be 1 because we are sending in 1 vec4 to the shader
    //glUniform4fv(uniloc, 1, color);

    ////check_gl_error();

    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //[> Make the window's context current <]
    //glClearColor(0.0f, 1.0f, 1.0f, 0.5f);


    //glfwSetKeyCallback(window, key_callback);
    //[> Loop until the user closes the window <]
    //while (!glfwWindowShouldClose(window)) {
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindVertexArray(vao);
        //// draw points 0-3 from the currently bound VAO with current in-use shader
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        ////update other events like input handling
        //glfwPollEvents();
        //if (should_quit_loop) break;
        //// put the stuff we've been drawing onto the display
        //glfwSwapBuffers(window);
    //}

    //glfwTerminate();
    //return 0;
//}

//}

//void shapegame::GLHandler::_check_gl_error(const char *file, int line) {
    //using namespace std;
    //GLenum err (glGetError());
    //while(err!=GL_NO_ERROR) {
        //string error;
        //switch(err) {
            //case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
            //case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
            //case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
            //case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
            //case 0x0506:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        //}

        //cerr << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<endl;
        //err=glGetError();
    //}
//}
