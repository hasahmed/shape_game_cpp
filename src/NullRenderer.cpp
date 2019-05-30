#include "shapegame.hpp"
#define ITERATIONS 1000

using namespace shapegame;

	NullRenderer::NullRenderer(Scene &scene) : scene(scene) {}
	void NullRenderer::setClearColor(Color& color){}
	void NullRenderer::run() {
		for (int i = 0; i < ITERATIONS; i++) {
			this->scene.updateChildren();
			this->scene.drawChildren();
			this->scene.killQueued();
		}
		// while(true){
		// }
	}
	void NullRenderer::draw(RenderPackage &rPack) {}
	void NullRenderer::initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) {}