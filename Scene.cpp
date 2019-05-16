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
	this->sceneChildren.push_back(std::move(obj));
}

void Scene::addMultiShapeChild(Object* obj) {
	obj->onAdd();
	if (auto mRaw = dynamic_cast<MultiShape*>(obj)) { //is multishape
		// auto mRaw = dynamic_cast<MultiShape*>(obj.release());
		// if (!mRaw) throw std::runtime_error("This really shouldn't have happened. Look for answers");
		// auto mUnique = std::unique_ptr<MultiShape>(mRaw);
		// this->addMultiShapeChild(std::move(mUnique));
		for (auto &obj : mRaw->getShapes()) {
			addMultiShapeChild(obj);
		}
	} else { // is not multishape
		// this->addToSceneChildren(std::move(obj));
		if (auto shape = dynamic_cast<Shape*>(obj)) { // if its a shape
			this->addShape(*shape);
		}
	}
}

void Scene::addMultiShape(std::unique_ptr<MultiShape> multi) {
	auto rawMulti = multi.get();
	this->addToSceneChildren(std::move(multi));
	for (auto &obj : rawMulti->shapeStorage) {
		addMultiShapeChild(obj.get());
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
		this->drawVect.insert({&shape, std::move(rPack)});
}

void Scene::addShape(Shape &shape) {
	this->addToDrawVect(shape);
}
Object* Scene::addChild(std::unique_ptr<Object> obj) { /* BASE IMPL */
	auto rawObj = obj.get();
	if (dynamic_cast<MultiShape*>(rawObj)) {
		// auto rawM = dynamic_cast<MultiShape*>(obj.release());
		// if (!rawM) throw std::runtime_error("Invariant Violation. Should never be null");
		// auto uniM = std::unique_ptr<MultiShape>(rawM);
		this->addMultiShape(std::unique_ptr<MultiShape>((MultiShape*)obj.release()));
		// this->addMultiShape(std::unique_ptr<MultiShape>(rawM));
	} else {
		this->addToSceneChildren(std::move(obj));
    if (Shape *s = dynamic_cast<Shape*>(rawObj)) {
			this->addShape(*s);
    }
	}
	return rawObj;
}
Object* shapegame::Scene::addChild(Object *obj) {
	return this->addChild(std::unique_ptr<Object>(obj));
}

void shapegame::Scene::drawChildren() {
	for (auto &child : this->sceneChildren) {
		drawChild(child.get());
	}
}
int i = 0;
void shapegame::Scene::drawChild(Object *child) {
	i++;
		// if (i > 2) { 
		// 	Shape *shape = dynamic_cast<Shape*>(child);
		// 	// if (!shape) {
		// 	// 	puts("Good");
		// 	// }
		// 	std::cout << shape << std::endl;
		// 	// std::cout << !!shape << std::endl;
		// 	exit(0);
		// }
	if (auto shape = dynamic_cast<Shape*>(child)) { // if its a shape
		auto rPack = this->drawVect.find(child);
		if (rPack == this->drawVect.end())
			throw std::runtime_error("There has been an error. Every shape should have a RenderPackage");
		Game::inst().draw(*rPack->second);
	} else if (auto mShape = dynamic_cast<MultiShape*>(child)) {
		for (auto mChild : mShape->getShapes()) {
			this->drawChild(mChild);
		}
	} // otherwise its a regular Object and nothing else needs to happen
}



void Scene::updateChildren() {
	int i = 0;
	for (auto &obj : this->sceneChildren) {
		i++; // record position in vector. I know I could just use iterators but nah
		obj->update();
		if (auto ent = dynamic_cast<Entity*>(obj.get())) {
			for (auto &compo : ent->compos) {
				compo->update(ent);
			}
		}
		if (obj->canKill) {
			this->killList.insert({i, obj.get()});
		}
	}
}

// room for improvement
void Scene::killQueued(){
	for (auto it: this->killList) {
		this->drawVect.erase(it.second);
		this->sceneChildren.erase(this->sceneChildren.begin() + it.first);
	}
	this->killList.clear();
}

void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}

void Scene::keyDispatch(int key, int action) {
    for (auto &obj: this->sceneChildren) {
        obj->onKeyPress((Input::Kb::Key)key, (Input::Action)action);
    }
}
void Scene::mouseBtnDispatch(int btn, int action) {
    for (auto &obj: this->sceneChildren) {
        obj->onMouseClick((Input::Mouse::Btn)btn,  (Input::Action)action);
    }
}