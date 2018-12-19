#include <memory>
#include <unistd.h>
#include <iterator>
#include "shapegame"
#include "Rectangle.hpp"


using namespace shapegame;
unsigned int nextInsert = 0;
unsigned int nextInsert2 = 0;

Scene* Scene::_inst= nullptr;

void Scene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (Scene::_inst && scancode) {
        _inst->keyDispatch(key, action);
    } else {
        puts("Scene not initlized yet. Keys cannot be processed");
    }
}


shapegame::Scene::Scene() :
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
        GLRenderObject renderObj = GLRenderObject();
        renderObj.vertexAttribIndex = GLHandler::getAssignableVertexAttribIndex();
        renderObj.verts = VertexGenerator::instance()->generate(*s);

        GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
        GLCALL(glUniform4fv(uniloc, 1, s->color.getRawColor()));

        GLCALL(glUseProgram(this->_shaderProg));
        GLCALL(glGenVertexArrays(1, &(renderObj.vao))); //generates vertex attribute array
        GLCALL(glGenBuffers(1, &(renderObj.vbo))); //generates 1 gpu buffer object
        GLCALL(glBindVertexArray(renderObj.vao)); //binds current buffers to current vao
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderObj.vbo)); //binds vbo to the array buffer portion of gpu memory?
        GLCALL(
            glBufferData(
                GL_ARRAY_BUFFER,
                renderObj.verts.size() * sizeof(float),
                &(renderObj.verts)[0],
                GL_DYNAMIC_DRAW
            )
        ); //dynamic because it will be modified often and updated often

        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
        GLCALL(glBindVertexArray(0)); //also an unbinding
        auto rPack = std::make_unique<RenderPackage>(s, &renderObj);
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
    // for (auto &r: this->drawVect) {
    for (auto it = this->drawVect.begin(); it != this->drawVect.end();) {
        if (it->second->shape->canKill) {
            it = this->drawVect.erase(it);
        } else {
            if (it->second->shape->collidable)
                this->collisionList->add(it->second->shape);
            auto &renderPack = it->second;
            GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
            GLCALL(glUniform4fv(uniloc, 1, renderPack->shape->color.getRawColor()));
            GLCALL(glBindVertexArray(renderPack->glRenderObject->vao));
            GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderPack->glRenderObject->vbo));

            if (renderPack->updateDirty()){
                GLCALL(
                    glBufferData(
                        GL_ARRAY_BUFFER,
                        renderPack->glRenderObject->verts.size() * sizeof(float),
                        &(renderPack->glRenderObject->verts)[0],
                        GL_DYNAMIC_DRAW
                    )
                );
            }
            GLCALL(
                glVertexAttribPointer(
                    renderPack->glRenderObject->vertexAttribIndex,
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    0
                )
            );
            GLCALL(glDrawArrays(GL_TRIANGLES, 0, renderPack->glRenderObject->verts.size()));
            GLCALL(glBindVertexArray(0));
            it++;
        }
    }
    this->collisionList->check();
    this->collisionList->clear();
}
void Scene::updateChildren() {
    for (auto it = this->sceneChildren.begin(); it != this->sceneChildren.end();) {
        if (it->second->canKill) {
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
        child.second->onKeyPress(key, action);
    }
}