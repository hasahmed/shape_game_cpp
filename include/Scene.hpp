#pragma once
#include <memory>
#include <vector>
#include <deque>
#include <unordered_map>
#include "Shape.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "GLHandler.hpp"
#include "GLRenderObject.hpp"
#include "RenderPackage.hpp"
#include "ShapePair.hpp"
#include "CollisionList.hpp"
#include "Color.hpp"


namespace shapegame {

    class Scene {
        friend class GLHandler;
        private:
            Color _bgColor;
            GLuint _shaderProg;
            void setShaderProg(GLuint shaderprog);
            std::unordered_map<unsigned int, std::unique_ptr<Object>> sceneChildren;
            std::unordered_map<unsigned int, std::unique_ptr<RenderPackage>> drawVect;
            static Scene *_inst;
        public:
            std::unique_ptr<CollisionList> collisionList;
            void updateChildren();
            void drawChildren(GLFWwindow *w);
            Object* addChild(Object *shape);
            template <class T>
            T* addChildAs(T *shape){
                static_assert(std::is_base_of<Object, T>::value, "T must extend Object");
                this->addChild(shape);
                return shape;
            }
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            void keyDispatch(int key, int action);
            void setBackgroundColor(Color& color);
            Scene();
    };
}
