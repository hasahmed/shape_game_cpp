#include <assert.h>
#include <string>
#include <iostream>
#include "../shapegame"
#include "Color.hpp"

using namespace shapegame;

//tests just create the colors
int main(){
	Color c(1, 2, 3);
	Color c1 = Color(c);
	Color c2 = Color(0.22, 0.11, 1.0, 0.123);
  std::cout << "Color.test.cpp Tests Passed" << std::endl;
}


