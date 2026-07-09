#include "shapegame.hpp"
using namespace shapegame;
// Copy constructor
ObjRenderWrapper::ObjRenderWrapper(std::unique_ptr<Object> pObj): obj(std::move(pObj)) {}
