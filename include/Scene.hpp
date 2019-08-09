#pragma once
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include "Shape.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "GLHandlerImpl.hpp"
#include "GLRenderObject.hpp"
#include "RenderPackage.hpp"
#include "ShapePair.hpp"
#include "CollisionList.hpp"
#include "Color.hpp"
#include "MultiShape.hpp"
#include "NullRenderer.hpp"


namespace shapegame {

	/*
		Wraps objects in with the components needed to render them
	*/
	struct ObjRenderWrapper {
		std::unique_ptr<Object> obj;
		std::vector<std::unique_ptr<RenderPackage>> rPacks;
		ObjRenderWrapper(std::unique_ptr<Object> pObj): obj(std::move(pObj)) {}
		// ObjRenderWrapper(std::unique_ptr<Object> pObj, RenderPackage* rPack): ObjRenderWrapper(std::move(pObj)) {
		// 	this->rPacks.emplace_back(*rPack);
		// }
		// void addRPack(RenderPackage *rPack) {
		// 	this->rPacks.emplace_back(std::move(*rPack));
		// }
	};

	class Scene {
			friend class GLHandlerImpl;
			friend class NullRenderer;
			friend class Window;
			private:
				Color _bgColor;
				GLuint _shaderProg;
				void setShaderProg(GLuint shaderprog);
				std::vector<Object*> killList;
				std::vector<std::unique_ptr<ObjRenderWrapper>> sceneChildren;
				static Scene *_inst;
				void initRenderables(ObjRenderWrapper &owr, Shape &shape);
				void addSubChild(ObjRenderWrapper &owr, Object* subObj);
				void killQueued();
				void drawChild(ObjRenderWrapper &owr);
				void updateChildren();
				void drawChildren();
				std::unique_ptr<CollisionList> collisionList;
				void addMultiShapeChild(Object* obj);
				static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void mouseBtnCallback(GLFWwindow* window, int btn, int action, int mods);
				void keyDispatch(int key, int action);
				void mouseBtnDispatch(int btn, int action);
			public:
				Scene();
				Object* addChild(Object *obj);
				Object* addChild(std::unique_ptr<Object> obj);
				template <class T>
				T* addChildAs(std::unique_ptr<Object> uniqueShape){
					auto rawPtr = uniqueShape.get();
					this->addChild(std::move(uniqueShape));
					if (auto typedPtr = dynamic_cast<T*>(rawPtr)) {
						return typedPtr;
					}
					throw std::runtime_error("Template function failed because couldn't dynamic cast to template type");
				}
				void setBackgroundColor(Color& color);
	};
}
