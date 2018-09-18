#include <memory>
#include "shapegame"
#define OBJECT_START_SIZE 100


shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}



//void shapegame::Scene::addChild(Drawable &drawable) {
    ////assignes but also increments for future users
    //drawable._vertexAttribIndex = this->_assignableVertexAttribIndex++;

    //GLCALL(glGenVertexArrays(1, &(drawable._vao))); //generates vertex attribute array
    //GLCALL(glGenBuffers(1, &(drawable._vbo))); //generates 1 gpu buffer object
    //GLCALL(glBindVertexArray(drawable._vao)); //binds current buffers to current vao
    //GLCALL(glBindBuffer(GL_ARRAY_BUFFER, drawable._vbo)); //binds vbo to the array buffer portion of gpu memory?
    //GLCALL(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), drawable._verts, GL_DYNAMIC_DRAW)); //dynamic because it will be modified often and updated often


    //GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

    //GLCALL(glEnableVertexAttribArray(0));
    //GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
    //GLCALL(glBindVertexArray(0)); //also an unbinding
    //_drawVect.push_back(drawable);
//}


//void shapegame::Scene::addChild(Shape &shape) {
//}
void shapegame::Scene::addChild(Shape &shape) {
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
    GLCALL(glBufferData(GL_ARRAY_BUFFER,
                renderObj.verts.size() * sizeof(float),
                &(renderObj.verts)[0],
                GL_DYNAMIC_DRAW)); //dynamic because it will be modified often and updated often

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
        GLCALL(glVertexAttribPointer(renderPack->glRenderObject->vertexAttribIndex,
                    renderPack->glRenderObject->verts.size() / 3, GL_FLOAT, GL_FALSE, 0, 0));
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, renderPack->glRenderObject->verts.size()));
        GLCALL(glBindVertexArray(0));

    }
}
void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}
