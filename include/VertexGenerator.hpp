#pragma once
#include "Scene.hpp"

namespace shapegame {
    class VertexGenerator {
        friend class Scene;

        private:
            static void triangleVerts();
    };
}
