#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "../shapegame"
#include "FileUtil.hpp"

//this mimics the data found in
// dummy-data/lines.txt
const char *strings = {
  "0\n"
  "1\n"
  "\n"
  "blank ^\n"
  "2\n"
  "3\n"
  "4\n"
  "5\n"
  "6\n"
  "7\n"
  "8\n"
  "9\n"
  "10\n"
  "\n"
  "\n"
  "^ two blanks\n"
  "one blank below\n"
  "\n"
};

int main(){
  std::string str = shapegame::FileUtil::read("dummy-data/lines.txt");
  for (int i = 0; i < str.size(); i++) {
      assert(std::string(1, str[i]).compare(std::string(1, strings[i])) == 0);
  }
  std::cout << "FileUtil.test.cpp Tests Passed" << std::endl;
}