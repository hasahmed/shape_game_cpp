#include "shapegame"

shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}

void shapegame::Scene::addChild(Drawable &drawable) {
    GLCALL(glGenVertexArrays(1, &(drawable._vao))); //generates vertex attribute array
    GLCALL(glGenBuffers(1, &(drawable._vbo))); //generates 1 gpu buffer object
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, drawable._vbo)); //binds vbo to the array buffer portion of gpu memory?
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * drawable._numVerts, drawable._verts, GL_DYNAMIC_DRAW)); //dynamic because it will be modified often and updated often
    _drawVect.push_back(drawable);
}

void shapegame::Scene::drawAll() {
    //for (auto &drawable : _drawVect) {
        //drawable.draw();
    //}
}

void shapegame::Scene::draw(Drawable &drawable) {

}
