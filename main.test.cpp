/**
 * 8 WAY Character
 * 
 */
#include "shapegame"
using namespace shapegame;

class KeyHandler : public Object {
    void onKeyPress(int key, int action) override {
        if (action != GLFW_PRESS) return;
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(Game::inst().getWindow()->window_handle, true);
        if (key == GLFW_KEY_1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (key == GLFW_KEY_2)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
};

class Player : public Triangle {
	const double speed = 250;
	public: 
	enum Dir {LEFT, RIGHT, NONE};
	// Dir DIR = Dir.LEFT;
		Player(double size=40, Position pos=Position(100, 100)): 
		Triangle(Position(0, 0), Point(size / 2, -size), Point(size, 0), Color::BLACK) {
			this->setPosition(pos);
		}

		// void onKeyPress(int key, int action) override {
		// 	if (key == GLFW_KEY_RIGHT) {
		// 		this->translate(speed * G::dt, 0);
		// }
		void update() override {
			// Input.Key.down()
			GLFWwindow *w = Game::inst().getWindow()->window_handle;
			if (glfwGetKey(w, GLFW_KEY_UP) && glfwGetKey(w, GLFW_KEY_RIGHT)) {
				this->translate(speed * G::dt, speed * G::dt * -1);
			} 
			else if (glfwGetKey(w, GLFW_KEY_UP) && glfwGetKey(w, GLFW_KEY_LEFT)) {
				this->translate(speed * G::dt * -1, speed * G::dt * -1);
			} 
			else if (glfwGetKey(w, GLFW_KEY_DOWN) && glfwGetKey(w, GLFW_KEY_RIGHT)) {
				this->translate(speed * G::dt, speed * G::dt);
			} 
			else if (glfwGetKey(w, GLFW_KEY_DOWN) && glfwGetKey(w, GLFW_KEY_LEFT)) {
				this->translate(speed * G::dt * -1, speed * G::dt);
			} 
			else if (glfwGetKey(w, GLFW_KEY_RIGHT)) {
				this->translate(speed * G::dt, 0);
			} 
			else if (glfwGetKey(w, GLFW_KEY_LEFT)) {
				this->translate(-(speed * G::dt), 0);
			}
			else if (glfwGetKey(w, GLFW_KEY_UP)) {
				this->translate(0, -(speed * G::dt));
			}
			else if (glfwGetKey(w, GLFW_KEY_DOWN)) {
				this->translate(0, (speed * G::dt));
			}
		}
};


int main() {
	Game game(1200, 700, "SHMUP");
	game.scene->addChild(new KeyHandler());
	game.scene->addChild(new Player());
	// game.scene->addChild(new Triangle(Position(10, 100), Point(50, 0), Point(90, 100), Color::BLACK));
	game.run();
}