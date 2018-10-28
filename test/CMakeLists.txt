cmake_minimum_required (VERSION 3.3)
set (CMAKE_CXX_STANDARD 17)
project (ShapeGameTests)
add_executable(FileUtil FileUtil.test.cpp ../FileUtil.cpp)