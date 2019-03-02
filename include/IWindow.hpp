#pragma once

struct GLFWwindow;

namespace shapegame {
	class IWindow {
		public:
			virtual GLFWwindow* getWindowHandle() const = 0;
			virtual int getHeight() = 0;
			virtual int getWidth() = 0;
			virtual ~IWindow() = default;
	};
} // shapegame
