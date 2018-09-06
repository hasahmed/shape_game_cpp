#include "shapegame"

shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}

void shapegame::Scene::addChild(Drawable &drawable) {
    //assignes but also increments for future users
    drawable._vertexAttribIndex = this->_assignableVertexAttribIndex++;

    GLCALL(glGenVertexArrays(1, &(drawable._vao))); //generates vertex attribute array
    GLCALL(glGenBuffers(1, &(drawable._vbo))); //generates 1 gpu buffer object
    GLCALL(glBindVertexArray(drawable._vao)); //binds current buffers to current vao
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, drawable._vbo)); //binds vbo to the array buffer portion of gpu memory?
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), drawable._verts, GL_DYNAMIC_DRAW)); //dynamic because it will be modified often and updated often


    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
    GLCALL(glBindVertexArray(0)); //also an unbinding
    _drawVect.push_back(drawable);
}

void shapegame::Scene::drawAll() {
    for (auto &drawable : _drawVect) {

        GLCALL(glBindVertexArray(drawable._vao));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, drawable._vbo));
        GLCALL(glVertexAttribPointer(drawable._vertexAttribIndex, 3, GL_FLOAT, GL_FALSE, 0, 0));
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, drawable._numVerts));
        GLCALL(glBindVertexArray(0));

    }
}
void shapegame::Scene::draw(Drawable &drawable) {

}
