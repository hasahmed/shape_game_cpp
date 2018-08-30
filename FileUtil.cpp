#include <iostream>
#include <fstream>
#include <vector>
#include "shapegame"

std::string shapegame::FileUtil::read(std::string path) {
    std::ifstream file(path);
    std::string buff;
    std::getline(file, buff, '\0');
    file.close();
    return buff;
}
