#include <assert.h>
#include <string>
#include <iostream>
#include "../shapegame"
#include "Object.hpp"

int main(){
  shapegame::Object o(10.2, 0.5);
  assert(o.pos.x() == 10.2f);
  assert(o.pos.y() == 0.5f);
  shapegame::Object o2(shapegame::Position(99.99, 5.123));
  assert(o2.pos.x() == 99.99f);
  assert(o2.pos.y() == 5.123f);
  std::cout << "Object.test.cpp Tests Passed" << std::endl;
}
