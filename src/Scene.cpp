#include <memory>
#include <unistd.h>
#include <iterator>
#include <algorithm>
#include "shapegame.hpp"
#include "Rectangle.hpp"


using namespace shapegame;
unsigned int nextInsert = 0;

Scene* Scene::_inst = nullptr;

void Scene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (Scene::_inst) {
        _inst->keyDispatch(key, action);
    } else {
        puts("Scene not initlized yet. Keys cannot be processed");
    }
}
void Scene::mouseBtnCallback(GLFWwindow* window, int btn, int action, int mods) {
    if (Scene::_inst) {
        _inst->mouseBtnDispatch(btn, action);
    } else {
        puts("Scene not initlized yet. Mouse Clicks Cannot Be Processed");
    }
}

void Scene::setBackgroundColor(Color& color) {
    this->_bgColor = color;
}

shapegame::Scene::Scene() :
    _bgColor(Color::BLUE),
    sceneChildren(),
    collisionList(new SimpleCollision())
		{
        Scene::_inst = this;
				sceneChildren.reserve(1000);
}

void Scene::initRenderables(ObjRenderWrapper &owr, Shape &shape) {
		GLRenderObject renderObj;
		Game::inst().initRenderObj(renderObj, shape, this->_shaderProg);
		owr.rPacks.emplace_back(shape, renderObj);
}

Object* Scene::addChild(Object *obj) {
	return this->addChild(std::unique_ptr<Object>(obj));
}

Object* Scene::addChild(std::unique_ptr<Object> obj) { /* BASE IMPL */
	ObjRenderWrapper &orw = this->sceneChildren.emplace_back(std::move(obj));
	Object *objRaw = orw.obj.get();
	objRaw->onAdd();

	if (auto *multi = dynamic_cast<MultiShape*>(objRaw)) {
		for (auto *subObj : multi->getShapes()) {
			addSubChild(orw, subObj);
		}
	} 
	else if (auto *shape = dynamic_cast<Shape*>(objRaw)) {
		initRenderables(orw, *shape);
	}
	else if (auto *object = dynamic_cast<Object*>(objRaw)) {
		// do nothing
	}
	return orw.obj.get();
}

void Scene::addSubChild(ObjRenderWrapper &owr, Object* subObj) {
	subObj->onAdd();
	if (auto *multi = dynamic_cast<MultiShape*>(subObj)) {
		for (auto *subObj : multi->getShapes()) {
			addSubChild(owr, subObj);
		}
	}
	else if (auto *shape = dynamic_cast<Shape*>(subObj)) {
		initRenderables(owr, *shape);
	}
	else if (auto *object = dynamic_cast<Object*>(subObj)) {
		// do nothing
	}
}

void Scene::drawChildren() {
	for (auto &orw : this->sceneChildren) {
		for (auto &rPack : orw.rPacks) {
			Game::inst().draw(rPack);
		}
	}
}

void Scene::updateChildren() {
	std::vector<ObjRenderWrapper*> childrenRefs;
	childrenRefs.reserve(this->sceneChildren.size());
	for (auto &orw : this->sceneChildren) {
		childrenRefs.push_back(&orw);
	}
	for (auto orw : childrenRefs) {
		orw->obj->update();
		if (auto ent = dynamic_cast<Entity*>(orw->obj.get())) {
			for (auto &compo : ent->compos) {
				compo->update(ent);
			}
		}
	}
}

void Scene::killQueued(){
	for (auto it = this->sceneChildren.begin(); it != this->sceneChildren.end();) {
		if (it->obj->canKill) {
			it->obj->onKill();
			for (auto &rPack : it->rPacks) {
				Game::inst().terminateRenderObj(rPack);
			}
			it = this->sceneChildren.erase(it);
		} else {
			++it;
		}
	}
}

void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}

void Scene::keyDispatch(int key, int action) {
    for (auto &orw : this->sceneChildren) {
       orw.obj->onKeyPress((Input::Kb::Key)key, (Input::Action)action);
    }
}
void Scene::mouseBtnDispatch(int btn, int action) {
    for (auto &orw : this->sceneChildren) {
        orw.obj->onMouseClick((Input::Mouse::Btn)btn,  (Input::Action)action);
    }
}