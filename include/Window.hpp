#pragma once
#include "shapegl.hpp"
#include <string>
#include "IWindow.hpp"
namespace shapegame {

	// class WindowInterface {
	// 	// virtual WindowInterface(int width, int height, std::string title) = 0;
	// 	public:
	// 		virtual int getHeight() = 0;
	// 		virtual int getWidth() = 0;
	// 		virtual std::string infoString() = 0;
	// 		virtual GLFWwindow* getWindowHandle() const = 0;
	// 		virtual WindowInterface* make(int width, int height, std::string title) = 0;
	// };

	class Window : public IWindow {
		private:
			Window(){}
			static Window _instance;
			int _width;
			int _height;
			const GLubyte* gl_renderer;
			const GLubyte* gl_version;
			GLFWwindow* windowHandle;
		public:
			// GLFWwindow* getWindowHandle();
			std::string infoString() ;
			Window(int width, int height, std::string window_title);
			GLFWwindow* getWindowHandle() const override;
			// static Window* getWindow();

			int getHeight() override;
			int getWidth() override;
	};

}
