cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)
project (FileUtilTest)
add_executable(FileUtil FileUtil.test.cpp ../FileUtil.cpp)
