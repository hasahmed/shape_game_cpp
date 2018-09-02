#include "shapegame"

shapegame::Scene::Scene() : _drawVect(), _sceneChildren() {}

void shapegame::Scene::addChild(GameObject obj) {
    _sceneChildren.push_back(obj);
}
