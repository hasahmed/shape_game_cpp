#include <assert.h>
#include <string>
#include <iostream>
#include "../shapegame"
#include "Shape.hpp"
#include "Globals.hpp"
#include "Color.hpp"

using namespace shapegame;
int main(){
	Shape s(100, 12, ShapeType::Triangle, Color::BLACK);
  assert(s.getHeight() == 100);
  assert(s.getWidth() == 12);
  assert(s.type == ShapeType::Triangle);
  assert(s.pos.getX() == 0.0);
  assert(s.pos.getY() == 0.0);

  Shape s1(-100, 12.2, ShapeType::Triangle, Position(10, -10), Color::WHITE);
  assert(s1.getHeight() == -100);
  assert(s1.getWidth() == 12.2f);
  assert(s1.type == ShapeType::Triangle);
  assert(s1.pos.getX() == 10);
  assert(s1.pos.getY() == -10);
  std::cout << "Shape.test.cpp Tests Passed" << std::endl;
}

