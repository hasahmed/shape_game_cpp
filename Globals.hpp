#pragma once
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>

#define gl_check_error() _gl_check_error(__FILE__,__LINE__)
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