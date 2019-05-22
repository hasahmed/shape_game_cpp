#pragma once
#include <memory>
#include <iostream>
#include "Shape.hpp"
#include "GLRenderObject.hpp"
namespace shapegame {
	class RenderPackage {
		public:
			Shape& shape; // Scene owns this Shape object
			std::unique_ptr<GLRenderObject> glRenderObject; // this should be more generic so that
			// the type of render object it holds could be arbitrary for other rendering systems
			~RenderPackage();
			RenderPackage(const RenderPackage &rPack); //copy ctor
			// RenderPackage(RenderPackage &&rPack); //move ctor
			RenderPackage(Shape &shape, GLRenderObject &glRenderObject);
			// void draw();
			bool updateDirty();
	};
}
