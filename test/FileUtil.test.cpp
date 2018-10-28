#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "../shapegame"
#include "FileUtil.hpp"

int main(){
  shapegame::FileUtil::read("dummy-data/lines.txt");
    // shapegame::FileUtil::read("../shaders/default.frag");
    //std::string str = shapegame::FileUtil::read("../shaders/default.frag");
    //std::cout << str;
}
