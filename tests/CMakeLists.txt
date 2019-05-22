cmake_minimum_required (VERSION 3.3)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_exes)
project (ShapeGameTests)
include_directories(../include)
include_directories(../deps)
include_directories(../deps/KHR)
include_directories(../deps/glad)
SET(CMAKE_EXE_LINKER_FLAGS "-lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
SET(ALL_SRCS
	../Color.cpp
	../Component.cpp
	../Debug.cpp
	../DebugKeyHandler.cpp
	../Drawable.cpp
	../Entity.cpp
	../FileUtil.cpp
	../GLHandlerImpl.cpp
	../GLRenderObject.cpp
	../Game.cpp
	../Globals.cpp
	../Input.cpp
	../MultiShape.cpp
	../NullGLHandler.cpp
	../NullRenderer.cpp
	../NullWindow.cpp
	../Object.cpp
	../Point.cpp
	../Position.cpp
	../Quad.cpp
	../Rectangle.cpp
	../RenderPackage.cpp
	../Scene.cpp
	../ShaderHandler.cpp
	../Shape.cpp
	../ShapePair.cpp
	../SimpleCollision.cpp
	../Timer.cpp
	../Tree.cpp
	../Triangle.cpp
	../TriangleIsosceles.cpp
	../VertexGenerator.cpp
	../Window.cpp
)
# SET(NO_GLFW_SRCS
# 	../Color.cpp
# 	../Component.cpp
# 	../Debug.cpp
# 	../DebugKeyHandler.cpp
# 	../Drawable.cpp
# 	../Entity.cpp
# 	../FileUtil.cpp
# 	../GLRenderObject.cpp
# 	../Game.cpp
# 	../Globals.cpp
# 	../Input.cpp
# 	../MultiShape.cpp
# 	../NullGLHandler.cpp
# 	../NullRenderer.cpp
# 	../NullWindow.cpp
# 	../Object.cpp
# 	../Point.cpp
# 	../Position.cpp
# 	../Quad.cpp
# 	../Rectangle.cpp
# 	../RenderPackage.cpp
# 	../Scene.cpp
# 	../ShaderHandler.cpp
# 	../Shape.cpp
# 	../ShapePair.cpp
# 	../SimpleCollision.cpp
# 	../Timer.cpp
# 	../Triangle.cpp
# 	../TriangleIsosceles.cpp
# 	../VertexGenerator.cpp
# )
add_executable(catch-tests catch-tests.cpp ${ALL_SRCS})

# add_executable(Object.test Object.test.cpp ${NO_GLFW_SRCS})
# add_executable(Triangle.test Triangle.test.cpp ${NO_GLFW_SRCS})
#  add_executable(MultiShape.test MultiShape.test.cpp ${NO_GLFW_SRCS})
#  add_executable(null-main.test null-main.test.cpp ${NO_GLFW_SRCS})
# add_executable(MultiShape.test.cpp ${ALL_SRCS})
# add_executable(FileUtil.test FileUtil.test.cpp ../FileUtil.cpp)
# add_etShapes().size() == 1);
	REQUIRE(t->removeShape(nullptr) == false);
	REQUIRE(t->getShapes().size() == 1);
}