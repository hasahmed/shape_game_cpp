cmake_minimum_required(VERSION 3.8)
project(shape_game_cpp)

set(CMAKE_CXX_STANDARD 17)
include_directories(deps)
include_directories(include)
if (_GLFW_COCOA)

    if (GLFW_USE_MENUBAR)
        set(_GLFW_USE_MENUBAR 1)
    endif()

    if (GLFW_USE_CHDIR)
        set(_GLFW_USE_CHDIR 1)
    endif()

    if (GLFW_USE_RETINA)
        set(_GLFW_USE_RETINA 1)
    endif()

    # Set up library and include paths
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    mark_as_advanced(COCOA_FRAMEWORK
            IOKIT_FRAMEWORK
            CORE_FOUNDATION_FRAMEWORK
            CORE_VIDEO_FRAMEWORK)
    list(APPEND glfw_LIBRARIES "${COCOA_FRAMEWORK}"
            "${IOKIT_FRAMEWORK}"
            "${CORE_FOUNDATION_FRAMEWORK}"
            "${CORE_VIDEO_FRAMEWORK}")

    set(glfw_PKG_DEPS "")
    set(glfw_PKG_LIBS "-framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo")
endif()


set(SOURCE_FILES
        Color.cpp
        Debug.cpp
        Drawable.cpp
        FileUtil.cpp
        Game.cpp
        GLHandler.cpp
        Globals.cpp
        Input.cpp
        main.cpp
        Object.cpp
        Position.cpp
        Rectangle.cpp
        RenderPackage.cpp
        Scene.cpp
        ShaderHandler.cpp
        Shape.cpp
        Timer.cpp
        Triangle.cpp
        VertexGenerator.cpp
        Window.cpp)

add_executable(shape_game_cpp ${SOURCE_FILES})