#include "../FileUtil.hpp"
#include <iostream>

int main(){
    auto x = shapegame::FileUtil::read_file("dummy-data/10-lines.txt");
    std::cout << x[0] << std::endl;
}
