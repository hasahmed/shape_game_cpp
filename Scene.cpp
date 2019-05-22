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
// void Scene::addToSceneChildren(std::unique_ptr<Object> obj) {
// 	// if (Game::inst().scene->shouldCheck) {
// 	// 	puts("Here");
// 	// }
// 	obj->onAdd();
// 	this->sceneChildren.push_back(std::move(obj));
// }

// void Scene::addMultiShapeChild(Object* obj) {
// 	obj->onAdd();
// 	if (auto mRaw = dynamic_cast<MultiShape*>(obj)) { //is multishape
// 		// auto mRaw = dynamic_cast<MultiShape*>(obj.release());
// 		// if (!mRaw) throw std::runtime_error("This really shouldn't have happened. Look for answers");
// 		// auto mUnique = std::unique_ptr<MultiShape>(mRaw);
// 		// this->addMultiShapeChild(std::move(mUnique));
// 		for (auto &obj : mRaw->getShapes()) {
// 			addMultiShapeChild(obj);
// 		}
// 	} else { // is not multishape
// 		// this->addToSceneChildren(std::move(obj));
// 		if (auto shape = dynamic_cast<Shape*>(obj)) { // if its a shape
// 			this->addShape(*shape);
// 		}
// 	}
// }


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
		// subKillList(),
    sceneChildren(),
    // drawVect(),
    collisionList(new SimpleCollision())
		{
        Scene::_inst = this;
				sceneChildren.reserve(1000);
}

void Scene::initRenderables(ObjRenderWrapper &owr, Shape &shape) {
		GLRenderObject renderObj;
		Game::inst().initRenderObj(renderObj, shape, this->_shaderProg);
		owr.rPacks.emplace_back(shape, renderObj);
		// auto rPack = std::make_unique<RenderPackage>(shape, renderObj);
		// this->drawVect.insert({&shape, std::move(rPack)});
}

// void Scene::addShape(Shape &shape) {
// 	this->addToDrawVect(shape);
// }

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
	// std::vector<Object*> childrenPtrs;
	// for (auto &child : this->sceneChildren) {
	// 	childrenPtrs.push_back(child.get());
	// }
	for (auto &orw : this->sceneChildren) {
		for (auto &rPack : orw.rPacks) {
			Game::inst().draw(rPack);
		}
	}
}
// void Scene::drawChild(Object *child) {
// 	if (auto shape = dynamic_cast<Shape*>(child)) { // if its a shape
// 		auto rPack = this->drawVect.find(shape);
// 		if (rPack == this->drawVect.end()) {
// 			// return;
// 			throw std::runtime_error("There has been an error. Every shape should have a RenderPackage");
// 		}
// 		Game::inst().draw(*rPack->second);
// 	} else if (auto mShape = dynamic_cast<MultiShape*>(child)) {
// 		for (auto mChild : mShape->getShapes()) {
// 			this->drawChild(mChild);
// 		}
// 	} // otherwise its a regular Object and nothing else needs to happen
// }

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
	// 	if (auto mShape = dynamic_cast<MultiShape*>(obj.get())) {
	// 		for (auto child : mShape->getShapes()) {
	// 			this->updateMultiChild(child); // first child index is 0
	// 		}
	// 	}
	// 	if (obj->canKill) {
	// 		this->killList.insert({i, obj.get()});
	// 	}
	// 	i++; // record position in vector for insertion in killList. I know I could just use iterators, but nah
	// }
	// for (auto &obj : this->queuedChildren) {
	// 	this->addChild(std::move(obj));
	// }
	// this->queuedChildren.clear();
// }
// void Scene::updateMultiChild(Object *child) {
// 		child->update();
// 		if (auto ent = dynamic_cast<Entity*>(child)) {
// 			for (auto &compo : ent->compos) {
// 				compo->update(ent);
// 			}
// 		}
// 		if (auto mShape = dynamic_cast<MultiShape*>(child)) {
// 			for (auto mChild : mShape->getShapes()) {
// 				this->updateMultiChild(mChild);
// 			}
// 		}
// 		if (child->canKill) {
// 			this->subKillList.push_back(child);
// 		}
// }

// void Scene::drawVectDelete(Object *shape) {
// 	Game::inst().terminateRenderObj(*this->drawVect.find(shape)->second);
// 	auto res = this->drawVect.erase(shape); //remove it from the drawVect
// }

void Scene::killQueued(){
	for (auto it = this->sceneChildren.begin(); it != this->sceneChildren.end(); ++it) {
		if (it->obj->canKill) {
			it->obj->onKill();
			it = this->sceneChildren.erase(it);
		}
	}
	// for (auto subChild : this->subKillList) { //loop through all things to be killed that are children of a multishape
	// 	if (dynamic_cast<Shape*>(subChild)){ // if it is a shape
	// 		this->drawVectDelete(subChild); //remove it from the drawVect
	// 	}
	// 	if (auto parent = dynamic_cast<MultiShape*>(subChild->getParent())){ //if its parent is a multishape (should never not be)
	// 		parent->removeShape(subChild); //then remove the shape from the parent
	// 	} else {
	// 		throw std::runtime_error("Error: No object should have a parent that is not a multishape");
	// 	}
	// }
	// for (auto it: this->killList) {
	// 	if (auto multi = dynamic_cast<MultiShape*>(it.second)){
	// 		killMulti(multi);
	// 	}
	// 	if (dynamic_cast<Shape*>(it.second)){
	// 		this->drawVectDelete(it.second);
	// 	}
	// 	std::cout << "Killed a: " << it.second->name << std::endl;
	// 	this->sceneChildren.erase(this->sceneChildren.begin() + it.first);
	// }
	// this->killList.clear();
	// this->subKillList.clear();
	// std::cout << "draw-vect-size : " << this->drawVect.size() << std::endl;
	// std::cout << "scene children size : " << this->sceneChildren.size() << std::endl;
	// std::cout << "kill-list-size" << this->killList.size() << std::endl;
	// std::cout << "sub-kill-list-size" << this->subKillList.size() << std::endl;
	// std::cout << "queuedChildren-size" << this->queuedChildren.size() << std::endl;
}

// void Scene::killMulti(Object *obj) {
// 	if (auto multi = dynamic_cast<MultiShape*>(obj)){
// 		for (auto &subShape : multi->getShapes()) {
// 			if (auto subMulti = dynamic_cast<MultiShape*>(subShape)){
// 				killMulti(subMulti);
// 			} else if (auto shape = dynamic_cast<Shape*>(subShape)) {
// 				this->drawVectDelete(shape);
// 			}
// 		}
// 	} else {
// 		if (auto shape = dynamic_cast<Shape*>(obj)) {
// 			this->drawVectDelete(shape);
// 		}
// 	}
// }

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