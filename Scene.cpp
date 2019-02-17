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
void Scene::addToSceneChildren(Object *obj) {
	this->sceneChildren.insert({
			nextInsert,
			std::unique_ptr<Object>(obj)
	});
	obj->onAdd();
}


void Scene::addMultiShape(MultiShape *multi) {
	this->addToSceneChildren(multi);
	for (Object *obj : multi->shapes) {
		Shape *s = dynamic_cast<Shape*>(obj);
		MultiShape *m = dynamic_cast<MultiShape*>(obj);
		if (s) {
			this->addShape(s);
		} else if (m) {
			this->addMultiShape(m);
		} else {
			this->addToSceneChildren(obj);
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

void Scene::addToDrawVect(Shape* shape) {
		GLRenderObject renderObj = GLRenderObject(*shape, this->_shaderProg);
		auto rPack = std::make_unique<RenderPackage>(*shape, renderObj);
		this->drawVect.insert({nextInsert, std::move(rPack)});
}

void Scene::addShape(Shape *shape) {
	this->addToDrawVect(shape);
	this->addToSceneChildren(shape);
}

// note instead of being passed a refrence I should really be passed a ponter.
// Then we wouldn't need a try block because the dynamic cast would return
// null instead of throwing
Object* shapegame::Scene::addChild(Object *obj) {
	/* Regular shape */
    Shape *s = dynamic_cast<Shape*>(obj);
		MultiShape *m = dynamic_cast<MultiShape*>(obj);
    if (s) {
			this->addShape(s);
    }
		 else if (m) {
			this->addMultiShape(m);
		} else {
			// plain old object
			this->addToSceneChildren(obj);
		}
		nextInsert++;
    return obj;
}

void shapegame::Scene::drawChildren(GLFWwindow *w) {
	for (auto &it : this->drawVect) {
		it.second->draw(w);
		// std::cout << it.first << ",";
		// if (it.second->shape.collidable)
			// this->collisionList->add(&(it.second->shape));
	}
	std::cout << "drawVect size: " << this->drawVect.size() << std::endl;
		// std::cout << std::endl << std::endl;
	// this->collisionList->check();
	// this->collisionList->clear();
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
	std::cout << "sceneChildren size: " << this->sceneChildren.size() << std::endl;
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