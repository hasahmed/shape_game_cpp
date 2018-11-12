#include <assert.h>
#include <string>
#include <iostream>
#include "../shapegame"
#include "Position.hpp"

int main(){
	shapegame::Position p(10, 100);
	assert(p.x() == 10);
	assert(p.y() == 100);
  std::cout << "Position.test.cpp Tests Passed" << std::endl;
}

