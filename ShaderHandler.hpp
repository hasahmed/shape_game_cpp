#pragma once
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace shapegame {

    class ShaderHandler{
        public:
        static std::string read_shader(std::string path);
    };
}
