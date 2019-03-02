#include "shapegame"

using namespace shapegame;

	NullRenderer::NullRenderer(Scene &scene) : scene(scene) {}
	void NullRenderer::setClearColor(Color& color){}
	void NullRenderer::run() {
		while(true){
			this->scene.updateChildren();
			this->scene.drawChildren();
			this->scene.killQueued();
		}
	}
	void NullRenderer::draw(RenderPackage &rPack) {}
	void NullRenderer::initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) {}