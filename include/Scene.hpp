#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "Drawable.hpp"
#include "GameObject.hpp"


namespace shapegame {
    class Scene {
        private:
            // used to determine the next index to use for glEnableVertexArrayAttrib
            int _assignableVertexAttribIndex = 0;
            std::vector<Drawable> _drawVect;
            std::vector<GameObject> _sceneChildren;
            //std::unordered_map<unsigned int, Drawable> _
        public:
            void drawAll();
            //void addChild(GameObject obj);
            void addChild(Drawable &drawable);
            void draw(Drawable &drawable);
            Scene();
    };
}
