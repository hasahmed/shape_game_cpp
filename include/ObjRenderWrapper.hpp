#pragma once
#include <memory>
#include <vector>
#include "RenderPackage.hpp"
namespace shapegame {
	/*
		Wraps objects in with the components needed to render them
	*/
	struct ObjRenderWrapper {
		std::unique_ptr<Object> obj;
		std::vector<std::unique_ptr<RenderPackage>> rPacks;
		ObjRenderWrapper(std::unique_ptr<Object> pObj);
	};
}
