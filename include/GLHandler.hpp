#pragma once
#include "Color.hpp"
namespace shapegame {
    class GLHandler{
			public:
				virtual void setClearColor(Color& color) = 0;
				virtual void run() = 0;
				virtual ~GLHandler() = default;
		};
}
