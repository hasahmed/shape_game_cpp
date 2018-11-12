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
            // used to determine the next index to use for glEnableVertexArrayAttrib
            std::vector<std::unique_ptr<RenderPackage>> _drawVect;
            std::vector<Object> _sceneChildren;
        public:
            void drawAll();
            //void addChild(GameObject obj);
            void addChild(const Shape &shape);
            //void draw(Triangle &drawable);
            Scene();
    };
}
