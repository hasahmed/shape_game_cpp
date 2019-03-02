#pragma once

#include "Color.hpp"
#include "RenderPackage.hpp"


namespace shapegame {
    class GLHandler{
			public:
				virtual void setClearColor(Color& color) = 0;
				virtual void run() = 0;
				virtual void draw(RenderPackage &rPack) = 0;
				virtual ~GLHandler() = default;
		};
}
