#include "shapegame"

shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}

void shapegame::Scene::addChild(GameObject obj) {
    _sceneChildren.push_back(obj);
}

void shapegame::Scene::drawAll() {
    for (auto &drawable : _drawVect) {
        drawable.draw();
    }
}
