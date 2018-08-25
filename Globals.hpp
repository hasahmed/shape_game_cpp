#pragma once
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#define DEBUG 1
#define GLCHECKERR() _gl_check_error(__FILE__,__LINE__)
#if DEBUG
#define GLCALL(gl_function) do {\
    gl_function;\
    GLCHECKERR();\
} while(0);
#else
#define GLCALL(gl_function) gl_function
#endif
namespace shapegame {
	void _gl_check_error(const char *file, int line) {
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
}
