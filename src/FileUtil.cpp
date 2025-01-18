#include <iostream>
#include <fstream>
#include <vector>
#include "shapegame.hpp"

std::string shapegame::FileUtil::read(std::string path) {
	//std::filesystem::path p = path;
	//std::ifstream file(p.make_preferred().string());
	std::ifstream file(path);
    std::string buff;
    std::getline(file, buff, '\0');
    file.close();
    return buff;
}
