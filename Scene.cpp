#include "shapegame"

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
void shapegame::Scene::addChild(Triangle &triangle) {
    //assignes but also increments for future users
    triangle._vertexAttribIndex = this->_assignableVertexAttribIndex++;
    //triangle._verts[0] -= 0.1;

    GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
    GLCALL(glUniform4fv(uniloc, 1, triangle.color._color));

    GLCALL(glUseProgram(this->_shaderProg));
    GLCALL(glGenVertexArrays(1, &(triangle._vao))); //generates vertex attribute array
    GLCALL(glGenBuffers(1, &(triangle._vbo))); //generates 1 gpu buffer object
    GLCALL(glBindVertexArray(triangle._vao)); //binds current buffers to current vao
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, triangle._vbo)); //binds vbo to the array buffer portion of gpu memory?
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangle._verts, GL_DYNAMIC_DRAW)); //dynamic because it will be modified often and updated often

    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
    GLCALL(glBindVertexArray(0)); //also an unbinding
    _drawVect.push_back(triangle);
}

void shapegame::Scene::drawAll() {
    for (auto &triangle : _drawVect) {

        GLint uniloc = glGetUniformLocation(this->_shaderProg, "incolor");
        GLCALL(glUniform4fv(uniloc, 1, triangle.color._color));
        GLCALL(glBindVertexArray(triangle._vao));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, triangle._vbo));
        GLCALL(glVertexAttribPointer(triangle._vertexAttribIndex, 3, GL_FLOAT, GL_FALSE, 0, 0));
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, triangle._numVerts));
        GLCALL(glBindVertexArray(0));

    }
}
void shapegame::Scene::setShaderProg(GLuint shaderProg) {
    this->_shaderProg = shaderProg;
}
