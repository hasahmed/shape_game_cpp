#pragma once
#include <memory>
#include <vector>
#include "Drawable.hpp"
#include "GameObject.hpp"


namespace shapegame {
    class Scene {
        private:
            std::unique_ptr<std::vector<Drawable>> _drawVect;
        public:
            void draw_all();
            void add_child(GameObject obj);
    };
}
