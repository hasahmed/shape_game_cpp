#pragma once

#include "IWindow.hpp"

namespace shapegame {
	class NullWindow : public IWindow{
			GLFWwindow* getWindowHandle() const override;
			int getHeight() override;
			int getWidth() override;
	};
	
} // shapegame