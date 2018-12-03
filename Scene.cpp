#include <memory>
#include <unistd.h>
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


shapegame::Scene::Scene() : sceneChildren(), drawVect() {
    Scene::_inst = this;
}

// note instead of being passed a refrence I should really be passed a ponter.
// Then we wouldn't need a try block because the dynamic cast would return
// null instead of throwing
void shapegame::Scene::addChild(Object &obj) {
    try {
        Shape& s = dynamic_cast<Shape&>(obj);
        GLRenderObject renderObj = GLRenderObject();
        renderObj.vertexAttribIndex = GLHandler::getAssignableVertexAttribIndex();
        renderObj.verts = VertexGenerator::instance()->generate(s);

        GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
        GLCALL(glUniform4fv(uniloc, 1, s._color._color));

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
        auto rPack = std::make_unique<RenderPackage>(&s, &renderObj);
        this->drawVect.insert({nextInsert, std::move(rPack)});
    } catch(const std::bad_cast& e) {
        //don't do anything, because this just
        // means that the object passed in is not a Shape
    }
    obj.onAdd();
    this->sceneChildren.insert({
        nextInsert,
        std::move(std::unique_ptr<Object>(&obj))
    });
    nextInsert++;
}

void shapegame::Scene::drawChildren(GLFWwindow *w) {
    for (auto &r: drawVect) {
        if (r.second->shape->canKill) {
            this->drawVect.erase(r.first);
        } else {
            auto &renderPack = r.second;
            GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
            GLCALL(glUniform4fv(uniloc, 1, renderPack->shape->_color._color));
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
        }
    }
}
void Scene::updateChildren() {
    for (auto &child : this->sceneChildren) {
        if (child.second->canKill) {
            // std::cout << "killing here" << std::endl;
            // auto &renderObj = this->drawVect[child.first];
            // renderObj->glRenderObject.reset();
            // this->drawVect.erase(child.first);

            // child.second.reset();
            // this->sceneChildren.erase(child.first);
            std::cout << child.first << std::endl;
        } else {
            child.second->update();
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