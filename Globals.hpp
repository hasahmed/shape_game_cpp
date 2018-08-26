#pragma once
#include <iostream>
#include "shapegame"
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
    void _gl_check_error(const char *file, int line);
}
