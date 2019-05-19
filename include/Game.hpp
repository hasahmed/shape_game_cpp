#pragma once
#include <memory>
#include "Window.hpp"
#include "GLHandler.hpp"
#include "Scene.hpp"
#include "VertexGenerator.hpp"
#include "RenderPackage.hpp"
#include "IWindow.hpp"


namespace shapegame {
	class Game {
		private:
			std::unique_ptr<IWindow> _window;
			std::unique_ptr<GLHandler> _glHandler;
			std::unique_ptr<VertexGenerator> _vertexGenerator;
			static Game *_inst;
		public:
			std::unique_ptr<Scene> scene;
			Game(
					unsigned int windowWidth,
					unsigned int windowHeight,
					std::string windowTitle
					);
			Game();
			static Game& inst();
			void draw(RenderPackage &rPack);
			void run();
			void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg);
			void terminateRenderObj(RenderPackage &rPack);
			IWindow const* getWindow();
	};
}
