#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ShaderHandler.hpp"

std::string shapegame::ShaderHandler::read_shader(std::string path) {
    //the file path is built here. note it doesn't support windows. Perhpas change later with boost or homeroll
    std::string shader_path(std::string("shaders") + std::string("/") + path);
    std::ifstream shader_file(shader_path);
    std::vector<std::string> file_buff;
    file_buff.push_back(std::string());
    if (shader_file.is_open()) {
        int i = 0;
        while (std::getline(shader_file, file_buff[i])) {
            file_buff.push_back(std::string());
            i++;
        }

        shader_file.close();
    } else std::cout << "unable to read shader " << shader_path << std::endl;
    // the count of how many characters are in the vector to know how big to make the buffer
    std::string concatinated_file;
    for (std::string line : file_buff) {
        if (!line.empty())
            concatinated_file += (line + "\n");
    }
    return concatinated_file;
}
