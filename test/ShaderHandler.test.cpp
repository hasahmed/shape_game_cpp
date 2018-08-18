#include "../ShaderHandler.hpp"
#include <iostream>

int main(){
    std::cout << shapegame::ShaderHandler::read_shader("../shaders/default.frag") << std::endl;
}
