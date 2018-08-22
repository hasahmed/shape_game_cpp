#include "../FileUtil.hpp"
#include <iostream>
#include <vector>

int main(){

    std::string str = shapegame::FileUtil::read("../shaders/default.frag");
    std::cout << str;
}
