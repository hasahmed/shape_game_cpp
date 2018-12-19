#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "Shape.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "GLHandler.hpp"
#include "GLRenderObject.hpp"
#include "RenderPackage.hpp"


namespace shapegame {

    class CollisionList {
        public:
            virtual void add(Shape*) = 0;
            virtual void clear() = 0;
            virtual void check() = 0;
            virtual ~CollisionList(){
            }
    };

    class SimpleCollision : public CollisionList {
        public:
            std::vector<Shape*> shapeStore_;
            SimpleCollision() : shapeStore_(){
                this->shapeStore_.reserve(100);
            }
            void add(Shape* shape) override {
                shapeStore_.push_back(shape);
            }
            void clear() override {
                this->shapeStore_.clear();
            }
            void check() override {
                for (unsigned int i = 0; i < this->shapeStore_.size(); i++) {
                    for (unsigned int j = 0; j < this->shapeStore_.size(); j++) {
                        if (this->shapeStore_[j] != this->shapeStore_[i]) {
                            if (this->shapeStore_[j]->isColliding(*(this->shapeStore_[i]))) {
                                this->shapeStore_[j]->onCollisionStart(*(this->shapeStore_[i]));
                                this->shapeStore_[i]->onCollisionStart(*(this->shapeStore_[j]));
                            }
                        }
                    }
                }
            }
    };

    class Scene {
        friend class GLHandler;
        private:
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
            Scene();
    };
}
