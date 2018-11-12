#include <memory>
#include "shapegame"
#define OBJECT_START_SIZE 100


std::ostream& operator<<( std::ostream& os, const std::unique_ptr<shapegame::RenderPackage>& rp){
    os << "Shape:" << std::endl;
    os << '\t';
    os << "_height: ";
    os << rp->shape->height() << std::endl;
    return os;
}

shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}

void shapegame::Scene::addChild(const Shape &shape) {
    auto renderObj = GLRenderObject();
    renderObj.vertexAttribIndex = GLHandler::getAssignableVertexAttribIndex();
    renderObj.verts = VertexGenerator::instance()->generate(shape);

    GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
    GLCALL(glUniform4fv(uniloc, 1, shape._color._color));

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

    //_drawVect.push_back(RenderPackage(&shape, &renderObj));
    auto x = std::make_unique<RenderPackage>(&shape, &renderObj);
    _drawVect.push_back(std::move(x));
}

void shapegame::Scene::drawAll() {
    for (auto &renderPack : _drawVect) {
        GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
        GLCALL(glUniform4fv(uniloc, 1, renderPack->shape->_color._color));
        GLCALL(glBindVertexArray(renderPack->glRenderObject->vao));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderPack->glRenderObject->vbo));
        // shapegame::Rectangle *triag = dynamic_cast<shapegame::Rectangle*>(renderPack->shape.get());
        // std::cout << triag << std::endl;
        // ((shapegame::Rectangle*)(renderPack->shape.get()))->update();
        // std::cout << (shapegame::Rectangle*)(renderPack->shape.get()) << std::endl;
        // triag->update();
        // renderPack->shape->update();
        // dynamic_cast<shapegame::Triangle*>(renderPack->shape.get())->update();
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
        // renderPack->glRenderObject->verts[0] += 0.02;
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
