#pragma once
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "GLHandler.hpp"
#include "Window.hpp"
class App {
	private:
		int window_height = 0;
		int window_width = 0;
	public:
		virtual void keyhandler(int key, int action) = 0;
		App(int window_height, int window_width, int=400, int=400);
};