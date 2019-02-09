cmake_minimum_required (VERSION 3.3)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_exes)
project (ShapeGameTests)
include_directories(../include)
include_directories(../deps)
include_directories(../deps/KHR)
include_directories(../deps/glad)
SET(CMAKE_EXE_LINKER_FLAGS "-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
SET(SRCS
	../Color.cpp
	../Debug.cpp
	../DebugKeyHandler.cpp
	../Drawable.cpp
	../FileUtil.cpp
	../GLHandler.cpp
	../GLRenderObject.cpp
	../Game.cpp
	../Globals.cpp
	../Input.cpp
	../MultiShape.cpp
	../Object.cpp
	../Point.cpp
	../Position.cpp
	../Rectangle.cpp
	../RenderPackage.cpp
	../Scene.cpp
	../ShaderHandler.cpp
	../Shape.cpp
	../ShapePair.cpp
	../SimpleCollision.cpp
	../Timer.cpp
	../Triangle.cpp
	../VertexGenerator.cpp
	../Window.cpp
)
message(${SRCS})
# add_executable(Object.test Object.test.cpp ../Object.cpp ../Point.cpp ../Position.cpp)
add_executable(MultiShape.test MultiShape.test.cpp ${SRCS})
# add_executable(FileUtil.test FileUtil.test.cpp ../FileUtil.cpp)
# add_executable(Position.test Position.test.cpp ../Position.cpp)
# add_executable(Color.test Color.test.cpp ../Color.cpp)
# add_executable(CollisionTree.test CollisionTree.test.cpp ../CollisionTree.cpp)
# add_executable(RenderPackage.test
# 							RenderPackage.test.cpp
# 							../RenderPackage.cpp
# 							../Shape.cpp
# 							../Position.cpp
# 							../Object.cpp
# 							../Color.cpp)CollisionTree.cpp../CollisionTree.cpp