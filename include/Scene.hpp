#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "Shape.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "GLHandler.hpp"
#include "GLRenderObject.hpp"
#include "RenderPackage.hpp"


namespace shapegame {
    class Scene {
        friend class GLHandler;
        private:
            GLuint _shaderProg;
            void setShaderProg(GLuint shaderprog);
            std::vector<std::unique_ptr<RenderPackage>> _drawVect;
            std::vector<std::unique_ptr<Object>> _sceneChildren;
        public:
            void updateChildren();
            void drawChildren(GLFWwindow *w);
            void addChild(Object &shape);
            Scene();
    };
}
