#include <iostream>
#include "shapegame.hpp"

using namespace shapegame;


void shapegame::_gl_check_error(const char *file, int line) {
    using namespace std;
    GLenum err(glGetError());
    while (err != GL_NO_ERROR) {
        string error;
        switch (err) {
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }

        cerr << "GL_" << error.c_str() << " - " << file << ":" << line << endl;
        err = glGetError();
    }
}

double G::dt = 1;
double G::fps = 0;