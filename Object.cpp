#include "shapegame"

using namespace shapegame;
Object::Object(double x, double y) : pos(x, y) {}
Object::Object(Position pos) : pos(pos) {}
Object::~Object(){}