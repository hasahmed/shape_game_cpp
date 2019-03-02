#pragma once

#include "GLHandler.hpp"
#include "Scene.hpp"

namespace shapegame { 
	class NullRenderer : public GLHandler {
		private:
			Scene &scene;
		public:
			NullRenderer(Scene &scene);
			void setClearColor(Color& color) override;
			void run() override;
			void draw(RenderPackage &rPack) override;
			virtual ~NullRenderer() = default;
	};
} // namespace shapegame
