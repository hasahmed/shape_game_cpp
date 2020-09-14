#include <memory>
//#include <unistd.h>
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
		auto rPack = std::make_unique<RenderPackage>(shape, renderObj);
		owr.rPacks.push_back(std::move(rPack));
}

Object* Scene::addChild(Object *obj) {
	return this->addChild(std::unique_ptr<Object>(obj));
}

Object* Scene::addChild(std::unique_ptr<Object> obj) { /* BASE IMPL */
	auto orw = std::make_unique<ObjRenderWrapper>(std::move(obj));
	ObjRenderWrapper *orwRaw = orw.get();
	Object *objRaw = orw->obj.get();
	this->sceneChildren.push_back(std::move(orw));
	objRaw->onAdd();

	if (auto *multi = dynamic_cast<MultiShape*>(objRaw)) {
		for (auto *subObj : multi->getShapes()) {
			addSubChild(*orwRaw, subObj);
		}
	} 
	else if (auto *shape = dynamic_cast<Shape*>(objRaw)) {
		initRenderables(*orwRaw, *shape);
	}
	else if (auto *object = dynamic_cast<Object*>(objRaw)) {
		// do nothing
	}
	return objRaw;
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
		for (auto &rPack : orw->rPacks) {
			Game::inst().draw(*rPack);
		}
	}
}

void Scene::updateChildren() {
	std::vector<ObjRenderWrapper*> childrenRefs;
	childrenRefs.reserve(this->sceneChildren.size());
	for (auto &orw : this->sceneChildren) {
		childrenRefs.push_back(orw.get());
	}
	for (auto orw : childrenRefs) {
		orw->obj->update();
		orw->obj->setDirty(false);
		orw->obj->rotationInfo.nextRotation = 0;
		orw->obj->rotationInfo.alternateOrigin = {};
		orw->obj->rotationInfo.hasAlternateOrigin = false;
		orw->obj->_nextScale = {};
		if (auto ent = dynamic_cast<Entity*>(orw->obj.get())) {
			for (auto &compo : ent->compos) {
				compo->update(ent);
			}
		}
	}
}

void Scene::killQueued(){
	for (std::vector<std::unique_ptr<ObjRenderWrapper>>::iterator it = this->sceneChildren.begin(); it != this->sceneChildren.end();) {
		ObjRenderWrapper &orw = **it;
		if (orw.obj->canKill) {
			orw.obj->onKill();
			for (auto &rPack : orw.rPacks) {
				Game::inst().terminateRenderObj(*rPack);
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
       orw->obj->onKeyPress((Input::Kb::Key)key, (Input::Action)action);
    }
}
void Scene::mouseBtnDispatch(int btn, int action) {
    for (auto &orw : this->sceneChildren) {
        orw->obj->onMouseClick((Input::Mouse::Btn)btn,  (Input::Action)action);
    }
}