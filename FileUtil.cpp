#include <iostream>
#include <fstream>
#include <vector>
#include "shapegame"

//std::vector<std::string> shapegame::FileUtil::read_file(std::string path) {
    ////the file path is built here. note it doesn't support windows. Perhpas change later with boost or homeroll
    //std::string file_path(path); //make the path platform agnostic someday
    //std::ifstream file(file_path);
    //std::vector<std::string> file_buff;
    //file_buff.push_back(std::string());
    //if (file.is_open()) {
        //int i = 0;
        //while (std::getline(file, file_buff[i])) {
            //file_buff.push_back(std::string());
            //i++;
        //}

        //file.close();
    //}
    //// the count of how many characters are in the vector to know how big to make the buffer
    //return file_buff;
//}

std::string shapegame::FileUtil::read(std::string path) {
    std::ifstream file(path);
    std::string buff;
    std::getline(file, buff, '\0');
    file.close();
    return buff;
}

//std::string shapegame::FileUtil::vect_to_str(std::vector<std::string> str_vect) {
    //std::string concatinated_file;
    //for (std::string line : str_vect) {
        //concatinated_file += (line + "\n");
    //}
    //return concatinated_file;
//}
