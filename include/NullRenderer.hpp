#pragma once

#include "GLHandler.hpp"

namespace shapegame { 
	class NullRenderer : public GLHandler {
		public:
			void setClearColor(Color& color) override;
			void run() override;
			void draw(RenderPackage &rPack) override;
	};
} // namespace shapegame
