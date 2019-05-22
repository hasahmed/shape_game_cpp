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
		std::vector<RenderPackage> rPacks;
		ObjRenderWrapper(std::unique_ptr<Object> pObj): obj(std::move(pObj)) {}
		ObjRenderWrapper(std::unique_ptr<Object> pObj, RenderPackage* rPack): ObjRenderWrapper(std::move(pObj)) {
			this->rPacks.emplace_back(*rPack);
		}
		void addRPack(RenderPackage *rPack) {
			this->rPacks.emplace_back(std::move(*rPack));
			// this->rPacks.push_back(std::move(rPack));
		}
	};

	class Scene {
			friend class GLHandlerImpl;
			friend class NullRenderer;
			private:
				Color _bgColor;
				GLuint _shaderProg;
				void setShaderProg(GLuint shaderprog);
				std::vector<Object*> killList;
				// std::vector<Object*> subKillList;
				std::vector<ObjRenderWrapper> sceneChildren;
				// std::vector<std::unique_ptr<Object>> queuedChildren;
				// std::unordered_map<Object*, std::unique_ptr<RenderPackage>> drawVect;
				static Scene *_inst;
				void initRenderables(ObjRenderWrapper &owr, Shape &shape);
				void addSubChild(ObjRenderWrapper &owr, Object* subObj);
				void killQueued();
				void drawChild(ObjRenderWrapper &owr);
				// void killMulti(Object *obj);
			public:
				bool shouldCheck = false;
				std::unique_ptr<CollisionList> collisionList;
				void updateChildren();
				void drawChildren();
				Object* addChild(Object *shape);
				Object* addChild(std::unique_ptr<Object> obj);
				void addMultiShapeChild(Object* obj);
				template <class T>
				T* addChildAs(T uniqueShape){
					auto rawPtr = uniqueShape.get();
					this->addChild(std::move(uniqueShape));
					return rawPtr;
				}
				static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void mouseBtnCallback(GLFWwindow* window, int btn, int action, int mods);
				void keyDispatch(int key, int action);
				void mouseBtnDispatch(int btn, int action);
				void setBackgroundColor(Color& color);
				int numChildren();
				Scene();
	};
}
