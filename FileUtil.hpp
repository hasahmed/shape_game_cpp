#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace shapegame {

    class FileUtil {
        public:
        static std::vector<std::string> read_file(std::string path);
        static std::string line_vect_to_str(std::vector<std::string> str_vect);
    };
}
