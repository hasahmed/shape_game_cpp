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

    class Scene {
        friend class GLHandlerImpl;
				friend class NullRenderer;
        private:
            Color _bgColor;
            GLuint _shaderProg;
            void setShaderProg(GLuint shaderprog);
						std::map<unsigned int, Object*> killList;
						std::vector<Object*> subKillList;
            std::vector<std::unique_ptr<Object>> sceneChildren;
            std::unordered_map<Object*, std::unique_ptr<RenderPackage>> drawVect;
            static Scene *_inst;
						void killQueued();
						void addMultiShape(std::unique_ptr<MultiShape> multi);
						void addToSceneChildren(std::unique_ptr<Object> obj);
						void addToDrawVect(Shape &shape);
						void addShape(Shape &shape);
            void drawChild(Object *child);
						void updateMultiChild(Object *child);
        public:
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
