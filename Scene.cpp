#include <memory>
#include <unistd.h>
#include <iterator>
#include <algorithm>
#include "shapegame"
#include "Rectangle.hpp"


using namespace shapegame;
unsigned int nextInsert = 0;

Scene* Scene::_inst = nullptr;

int Scene::numChildren() {
	return this->sceneChildren.size();
}
void Scene::addToSceneChildren(std::unique_ptr<Object> obj) {
	obj->onAdd();
	this->sceneChildren.insert({
			nextInsert,
			std::move(obj)
	});
}

void Scene::addMultiShape(std::unique_ptr<MultiShape> multi) {
	auto rawMulti = multi.get();
	this->addToSceneChildren(std::move(multi));
	for (auto &obj : rawMulti->unAddedShapes) {
		if (dynamic_cast<MultiShape*>(obj.get())) {
			auto mRaw = dynamic_cast<MultiShape*>(obj.release());
			if (!mRaw) throw std::runtime_error("This really shouldn't have happened. Look for answers");
			auto mUnique = std::unique_ptr<MultiShape>(mRaw);
			this->addMultiShape(std::move(mUnique));
		} else {
			auto objRaw = obj.get();
			this->addToSceneChildren(std::move(obj));
			if (auto shape = dynamic_cast<Shape*>(objRaw)) { // if its a shape
				this->addShape(*shape);
			}
		}
	}
}

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
    drawVect(),
    collisionList(new SimpleCollision()
		){
        Scene::_inst = this;
}

void Scene::addToDrawVect(Shape &shape) {
		GLRenderObject renderObj;
		Game::inst().initRenderObj(renderObj, shape, this->_shaderProg);
		// GLRenderObject renderObj = GLRenderObject(shape, this->_shaderProg);
		auto rPack = std::make_unique<RenderPackage>(shape, renderObj);
		this->drawVect.insert({nextInsert, std::move(rPack)});
}

void Scene::addShape(Shape &shape) {
	this->addToDrawVect(shape);
}
Object* Scene::addChild(std::unique_ptr<Object> obj) {
	auto rawObj = obj.get();
	if (dynamic_cast<MultiShape*>(rawObj)) {
		auto rawM = dynamic_cast<MultiShape*>(obj.release());
		if (!rawM) throw std::runtime_error("Invariant Violation. Should never be null");
		auto uniM = std::unique_ptr<MultiShape>(rawM);
		this->addMultiShape(std::move(uniM));
	} else {
		this->addToSceneChildren(std::move(obj));
    if (Shape *s = dynamic_cast<Shape*>(rawObj)) {
			this->addShape(*s);
    }
	}
	nextInsert++;
	return rawObj;
}
Object* shapegame::Scene::addChild(Object *obj) {
	return this->addChild(std::unique_ptr<Object>(obj));
}

void shapegame::Scene::drawChildren() {
	for (auto &it : this->drawVect) {
		Game::inst().draw(*it.second);
		// it.second->draw();
	}
}

void Scene::updateChildren() {
	for (auto &it : this->sceneChildren) {
		it.second->update();
		// std::cout << it.first << ",";
		auto ent = dynamic_cast<Entity*>(it.second.get());
		if (ent) {
			for (auto &compo : ent->compos) {
				compo->update(ent);
			}
		}
		if (it.second->canKill) {
			this->killList.push_back(it.first);
		}
	}
	// std::cout << "sceneChildren size: " << this->sceneChildren.size() << std::endl;
		// std::cout << std::endl << std::endl;
}

// room for improvement
void Scene::killQueued(){
	for (auto killKey : this->killList) {
		this->drawVect.erase(killKey);
		this->sceneChildren.erase(killKey);
	}
	this->killList.clear();
}

void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}

void Scene::keyDispatch(int key, int action) {
    for (auto &child : this->sceneChildren) {
        child.second->onKeyPress((Input::Kb::Key)key, (Input::Action)action);
    }
}
void Scene::mouseBtnDispatch(int btn, int action) {
    for (auto &child : this->sceneChildren) {
        child.second->onMouseClick((Input::Mouse::Btn)btn,  (Input::Action)action);
    }
}