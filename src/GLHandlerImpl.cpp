#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "shapegame.hpp"
#include "GLRenderObject.hpp"


using namespace shapegame;

int shapegame::GLHandlerImpl::_assignableVertexAttribIndex = 0;

float color[4] = {1.0, 1.0, 0.0, 1.0};


void GLHandlerImpl::setClearColor(Color& color) {
    this->_clearColor = color;
    GLCALL(glClearColor(
        this->_clearColor.r,
        this->_clearColor.g,
        this->_clearColor.b,
        this->_clearColor.a
    ));
}

shapegame::GLHandlerImpl::GLHandlerImpl(IWindow *window, Scene &scene) :
    _scene(scene),
    _clearColor(Color::BLACK)
{
    this->windowHandle = window->getWindowHandle();

    //compile and link shaders
    //------------------------------------------------------------------------
    //vert
    // std::string _vert_shader = FileUtil::read("shaders/default.vert");
    const char *vertex_shader =
		"#version 410 core\n"
		"in vec3 vp;\n"
		"void main() {\n"
				"gl_Position.xyz = vp;\n"
				"gl_Position.w = 1.0;\n"
		"}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLCALL(glShaderSource(vs, 1, &vertex_shader, NULL));
    GLCALL(glCompileShader(vs));
    check_shader_err(vs);
    //end vert

    //frag
    // std::string _frag_shader = FileUtil::read("shaders/default.frag");
		const char *fragment_shader = 
			"#version 410 core\n"
			"out vec4 frag_color;\n"
			"uniform vec4 incolor;\n"
			"uniform vec3 mouse;\n"
			"uniform vec2 screen_res;\n"
			"uniform float u_time;\n"
			"void main() {\n"
					"frag_color = incolor;\n"
			"}\n";

		// _frag_shader.c_str();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLCALL(glShaderSource(fs, 1, &fragment_shader, NULL));
    GLCALL(glCompileShader(fs));
    check_shader_err(fs);
    //end frag


    //shader prog
    this->shader_prog = glCreateProgram();
    scene.setShaderProg(this->shader_prog);
    GLCALL(glBindAttribLocation(this->shader_prog, 2, "mouse_vert"));
    //std::cout << this->shader_prog << std::endl;
    GLCALL(glAttachShader(this->shader_prog, fs));
    GLCALL(glAttachShader(this->shader_prog, vs));
    GLCALL(glLinkProgram(this->shader_prog));
    check_shader_err(fs);
    GLCALL(glUseProgram(this->shader_prog));
    //end shader prog

    //delete shader
    GLCALL(glDeleteShader(fs));
    GLCALL(glDeleteShader(vs));
    //end delete shader



    //vbo
    GLCALL(glGenVertexArrays(1, &vao)); //generates vertex attribute array
    GLCALL(glGenBuffers(1, &vbo)); //generates 1 gpu buffer object
    GLCALL(glBindVertexArray(vao)); //binds current buffers to current vao
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo)); //binds vbo to the array buffer portion of gpu memory?
    // GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(square_points), square_points, GL_DYNAMIC_DRAW));
    //dynamic because it will be modified often and updated often


    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
    GLCALL(glBindVertexArray(0)); //also an unbinding

    //input to shader program
    GLint uniloc = glGetUniformLocation(this->shader_prog, "incolor");
    GLCALL(glUniform4fv(uniloc, 1, color));
    uniloc = glGetUniformLocation(this->shader_prog, "screen_res");
    GLCALL(glUniform2f(uniloc, window->getWidth(), window->getHeight()));
    check_shader_err(vs);


    // other gl settings

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glClearColor(
        this->_clearColor.r,
        this->_clearColor.g,
        this->_clearColor.b,
        this->_clearColor.a
    ));


// uncomment if back culling is desired
    // GLCALL(glCullFace(GL_BACK));
    // GLCALL(glEnable(GL_CULL_FACE));
		GLCALL(glDepthFunc(GL_NEVER));


}
void shapegame::GLHandlerImpl::check_shader_err(int shader){
    char infoLog[512];
    int success = 1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void GLHandlerImpl::terminateRenderObj(RenderPackage &rPack) {
	auto &renderObj = *rPack.glRenderObject;
	GLCALL(glDeleteVertexArrays(1, &(renderObj.vao)));
	GLCALL(glDeleteBuffers(1, &(renderObj.vbo)));
}

void GLHandlerImpl::draw(RenderPackage &rPack) {
	auto &renderObj = *rPack.glRenderObject;
	GLint uniloc = glGetUniformLocation(renderObj.shaderProg, "incolor");
	GLCALL(glUniform4fv(uniloc, 1, rPack.shape.color.getRawColor()));
	GLCALL(glBindVertexArray(renderObj.vao));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderObj.vbo));

	if (rPack.updateDirty()){
		GLCALL(
			glBufferData(
				GL_ARRAY_BUFFER,
				renderObj.numVerts * sizeof(float),
				renderObj.verts,
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
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, renderObj.numVerts));
	GLCALL(glBindVertexArray(0));
}

void GLHandlerImpl::initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) {
	rObj.shaderProg = shaderProg;
	rObj.vertexAttribIndex = 0;
	VertexGenerator::instance()->generate(shape, rObj.verts);

	GLint uniloc = glGetUniformLocation(rObj.shaderProg, "incolor");
	GLCALL(glUniform4fv(uniloc, 1, shape.color.getRawColor()));

	GLCALL(glUseProgram(rObj.shaderProg));
	GLCALL(glGenVertexArrays(1, &(rObj.vao))); //generates vertex attribute array
	GLCALL(glGenBuffers(1, &(rObj.vbo))); //generates 1 gpu buffer object
	GLCALL(glBindVertexArray(rObj.vao)); //binds current buffers to current vao
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rObj.vbo)); //binds vbo to the array buffer portion of gpu memory?
	GLCALL(
		glBufferData(
			GL_ARRAY_BUFFER,
			rObj.numVerts * sizeof(float),
			rObj.verts,
			GL_DYNAMIC_DRAW
		)
	); //dynamic because it will be modified often and updated often

	GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); //this is actually an unbinding
	GLCALL(glBindVertexArray(0)); //also an unbinding

}

void shapegame::GLHandlerImpl::run() {
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    while (!glfwWindowShouldClose(this->windowHandle)) {
        auto t2 = Clock::now();
        std::chrono::duration<double> elapsed_seconds = t2 - t1;
        // glfwGetCursorPos(this->windowHandle, &mouse_x, &mouse_y);
        this->setClearColor(this->_scene._bgColor);
        //int mouse_pressed = glfwGetMouseButton(this->windowHandle, GLFW_MOUSE_BUTTON_LEFT);
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        _scene.updateChildren();
        _scene.drawChildren();
				_scene.killQueued();

				// std::cout << "\r";
				// std::cout << std::flush;
				// std::cout << "drawChildren:" << _scene.drawVect.size() << std::endl;
				// std::cout << "\rdrawChildren:" << _scene.drawVect.size();
				// std::cout << "\rsceneChildren:" << _scene.sceneChildren.size();

        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapInterval(1);
        glfwSwapBuffers(this->windowHandle);
        std::chrono::duration<double> frameLength = Clock::now() - t2;
				G::dt = frameLength.count();
				G::fps = 1.0f / G::dt;
    }

    glfwTerminate();
}
