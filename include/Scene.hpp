#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "Drawable.hpp"
#include "GameObject.hpp"
#include "Triangle.hpp"
#include "GLHandler.hpp"


namespace shapegame {
    class Scene {
        friend class GLHandler;
        private:
            GLuint _shaderProg;
            void setShaderProg(GLuint shaderprog);
            // used to determine the next index to use for glEnableVertexArrayAttrib
            int _assignableVertexAttribIndex = 0;
            //std::vector<Triangle> _drawVect;
            std::vector<Triangle> _drawVect;
            std::vector<GameObject> _sceneChildren;
            //std::unordered_map<unsigned int, Drawable> _
        public:
            void drawAll();
            //void addChild(GameObject obj);
            void addChild(Triangle &drawable);
            //void draw(Triangle &drawable);
            Scene();
    };
}
