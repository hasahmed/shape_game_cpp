#include <memory>
#include <unistd.h>
#include "shapegame"
#include "Rectangle.hpp"
#define OBJECT_START_SIZE 100

using namespace shapegame;

shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}

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
        rPack->shape->onAdd();
        _drawVect.push_back(std::move(rPack));
    } catch(const std::bad_cast& e) {
        std::cout << "bad cast" << std::endl;
    }
    this->_sceneChildren.push_back(
        std::move(
            std::unique_ptr<Object>(&obj)
        )
    );

}

void shapegame::Scene::drawAll(GLFWwindow *w) {
    // for (auto &renderPack : _drawVect) {
    for (std::unique_ptr<RenderPackage> &renderPack : _drawVect) {
        GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
        GLCALL(glUniform4fv(uniloc, 1, renderPack->shape->_color._color));
        GLCALL(glBindVertexArray(renderPack->glRenderObject->vao));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderPack->glRenderObject->vbo));

       renderPack->shape->update();
        if (renderPack->updateDirty()){
            GLCALL(
                glBufferData(
                    GL_ARRAY_BUFFER,
                    renderPack->glRenderObject->verts.size() * sizeof(float),
                    //  sizeof(float),
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
void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}
