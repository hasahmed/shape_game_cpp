#include <assert.h>
#include <string>
#include <iostream>
#include "../shapegame"

using namespace shapegame;
int main(){
	Object o(10.2, 0.5);
	o.pos.setX(100);
	auto x = new Object();
	delete x;
  // assert(o.pos.getX() == 10.2f);
  // assert(o.pos.getY() == 0.5f);
  // shapegame::Object o2(shapegame::Position(99.99, 5.123));
  // assert(o2.pos.getX() == 99.99f);
  // assert(o2.pos.getY() == 5.123f);
  // std::cout << "Object.test.cpp Tests Passed" << std::endl;
}
