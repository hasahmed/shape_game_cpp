cmake_minimum_required (VERSION 3.3)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_exes)
project (ShapeGameTests)
include_directories(../include)
add_executable(FileUtil.test FileUtil.test.cpp ../FileUtil.cpp)
add_executable(Position.test Position.test.cpp ../Position.cpp)
add_executable(Color.test Color.test.cpp ../Color.cpp)
add_executable(Object.test Object.test.cpp ../Object.cpp ../Position.cpp)
add_executable(Shape.test
							Shape.test.cpp
							../Shape.cpp
							../Position.cpp
							../Object.cpp
							../Color.cpp)
add_executable(RenderPackage.test
							RenderPackage.test.cpp
							../RenderPackage.cpp
							../Shape.cpp
							../Position.cpp
							../Object.cpp
							../Color.cpp)