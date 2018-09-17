#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "Shape.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "GLHandler.hpp"
#include "GLRenderObject.hpp"


namespace shapegame {
    class Scene {
        friend class GLHandler;
        private:
            GLuint _shaderProg;
            void setShaderProg(GLuint shaderprog);
            // used to determine the next index to use for glEnableVertexArrayAttrib
            int _assignableVertexAttribIndex = 0;
            //std::vector<Triangle> _drawVect;
            std::vector<Shape> _drawVect;
            std::vector<Object> _sceneChildren;
            std::unordered_map<int, Shape> _glRenderObjects;
        public:
            void drawAll();
            //void addChild(GameObject obj);
            void addChild(Shape &shape);
            //void draw(Triangle &drawable);
            Scene();
    };
}
