#pragma once
#include <memory>
#include <vector>
#include "Drawable.hpp"
#include "GameObject.hpp"


namespace shapegame {
    class Scene {
        private:
            std::vector<Drawable> _drawVect;
            std::vector<GameObject> _sceneChildren;
        public:
            void drawAll();
            void addChild(GameObject obj);
            Scene();
    };
}
