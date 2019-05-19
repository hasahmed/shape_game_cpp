#pragma once

#include "Color.hpp"
#include "RenderPackage.hpp"
#include "GLRenderObject.hpp"


namespace shapegame {
    class GLHandler{
			public:
				virtual void setClearColor(Color& color) = 0;
				virtual void run() = 0;
				virtual void draw(RenderPackage &rPack) = 0;
				virtual void terminateRenderObj(RenderPackage &rPack) = 0;
				virtual void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) = 0;
				virtual ~GLHandler() = default;
		};
}
