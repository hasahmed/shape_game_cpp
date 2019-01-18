#include "shapegame"

using namespace shapegame;

GLRenderObject::GLRenderObject(Shape &s, GLuint shaderProg): shaderProg(shaderProg) {
	this->vertexAttribIndex = 0;
	this->verts = VertexGenerator::instance()->generate(s);

	GLint uniloc = glGetUniformLocation(this->shaderProg, "incolor");
	GLCALL(glUniform4fv(uniloc, 1, s.color.getRawColor()));

	GLCALL(glUseProgram(this->shaderProg));
	GLCALL(glGenVertexArrays(1, &(this->vao))); //generates vertex attribute array
	GLCALL(glGenBuffers(1, &(this->vbo))); //generates 1 gpu buffer object
	GLCALL(glBindVertexArray(this->vao)); //binds current buffers to current vao
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->vbo)); //binds vbo to the array buffer portion of gpu memory?
	GLCALL(
		glBufferData(
			GL_ARRAY_BUFFER,
			this->verts.size() * sizeof(float),
			&(this->verts)[0],
			GL_DYNAMIC_DRAW
		)
	); //dynamic because it will be modified often and updated often

	GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
	GLCALL(glBindVertexArray(0)); //also an unbinding

}
