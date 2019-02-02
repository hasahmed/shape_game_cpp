#include <memory>
#include <unistd.h>
#include <iterator>
#include "shapegame"
#include "Rectangle.hpp"


using namespace shapegame;
unsigned int nextInsert = 0;
unsigned int nextInsert2 = 0;

Scene* Scene::_inst = nullptr;

void Scene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (Scene::_inst && scancode) {
        _inst->keyDispatch(key, action);
    } else {
        puts("Scene not initlized yet. Keys cannot be processed");
    }
}

void Scene::setBackgroundColor(Color& color) {
    this->_bgColor = color;
}

shapegame::Scene::Scene() :
    _bgColor(Color::BLUE),
    sceneChildren(),
    drawVect(),
    collisionList(new SimpleCollision())
    {
        Scene::_inst = this;
}

// note instead of being passed a refrence I should really be passed a ponter.
// Then we wouldn't need a try block because the dynamic cast would return
// null instead of throwing
Object* shapegame::Scene::addChild(Object *obj) {
    Shape *s = dynamic_cast<Shape*>(obj);
    if (s) {
        GLRenderObject renderObj = GLRenderObject(*s, this->_shaderProg);
        auto rPack = std::make_unique<RenderPackage>(*s, renderObj);
        this->drawVect.insert({nextInsert, std::move(rPack)});
    }
    obj->onAdd();
    this->sceneChildren.insert({
        nextInsert,
        std::move(std::unique_ptr<Object>(obj))
    });
    nextInsert++;
    return obj;
}

void shapegame::Scene::drawChildren(GLFWwindow *w) {
    for (auto it = this->drawVect.begin(); it != this->drawVect.end();) {
        if (it->second->shape.canKill) {
            throw std::runtime_error("No killed shapes should make it to the draw call");
        } else {
            if (it->second->shape.collidable)
                this->collisionList->add(&(it->second->shape));
								it->second->draw(w);
            it++;
        }
    }
    this->collisionList->check();
    this->collisionList->clear();
}
void Scene::updateChildren() {
    for (auto it = this->sceneChildren.begin(); it != this->sceneChildren.end();) {
        if (it->second->canKill) {
            Shape *s = dynamic_cast<Shape*>(it->second.get());
            if (s) { // then it is a shape
                this->collisionList->remove(s);
            }
            it->second->onRemove();
            this->drawVect.erase(it->first);
            it = (this->sceneChildren.erase(it));
        } else {
            it->second->update();
            it++;
        }
    }
}

void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}

void Scene::keyDispatch(int key, int action) {
    for (auto &child : this->sceneChildren) {
        child.second->onKeyPress((Input::Key)key, action);
    }
}