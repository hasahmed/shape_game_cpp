#include "../FileUtil.hpp"
#include <iostream>
#include <vector>

int main(){

    std::string str = shapegame::FileUtil::read("dummy-data/lines.txt");
    std::cout << str;
}
