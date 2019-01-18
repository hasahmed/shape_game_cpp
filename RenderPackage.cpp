#include <memory>
#include <iostream>
#include "shapegame"

using namespace shapegame;

RenderPackage::RenderPackage(Shape &shape,
        GLRenderObject &glRenderObject): shape(shape) {
    this->glRenderObject = std::make_unique<GLRenderObject>(glRenderObject);
}
bool RenderPackage::updateDirty() {
    if (this->shape._dirty){
        // super waste. Don't throw away verticies, move them instead.
        this->glRenderObject->verts = VertexGenerator::instance()->generate(this->shape);
        this->shape._dirty = false;
        return true;
    }
    return false;
}

void RenderPackage::draw(GLFWwindow *w) {
	auto &renderObj = *this->glRenderObject;
	GLint uniloc = glGetUniformLocation(renderObj.shaderProg, "incolor");
	GLCALL(glUniform4fv(uniloc, 1, this->shape.color.getRawColor()));
	GLCALL(glBindVertexArray(renderObj.vao));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderObj.vbo));

	if (this->updateDirty()){
		GLCALL(
			glBufferData(
				GL_ARRAY_BUFFER,
				renderObj.verts.size() * sizeof(float),
				&(renderObj.verts)[0],
				GL_DYNAMIC_DRAW
			)
		);
	}
	GLCALL(
		glVertexAttribPointer(
			renderObj.vertexAttribIndex,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		)
	);
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, renderObj.verts.size()));
	GLCALL(glBindVertexArray(0));
}