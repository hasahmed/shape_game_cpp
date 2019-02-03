/**
 * 8 WAY Character
 * 
 */
#include "shapegame"
#include <cstdlib>
using namespace shapegame;
using namespace shapegame::Input;

class KeyHandler : public Object {
    void onKeyPress(Kb::Key key, Input::Action action) override {
        if (action != Action::DOWN) return; // skip up actions
        if (key == Kb::Key::ESCAPE)
            glfwSetWindowShouldClose(Game::inst().getWindow()->window_handle, true);
        if (key == Kb::Key::N1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (key == Kb::Key::N2)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
};

// class Projectile : public Rectangle {
class Projectile : public Triangle {
	public:
	const int SPEED = rand() % 100;
	Projectile(Position pos, Point size = Point(10, 50)):
		// Rectangle(size.getY(), size.getX(), pos, Color::WHITE) {
		Triangle(Position(0.0, 0.0), Point(5, -20), Point(10, 0), Color::WHITE) {
			this->setPosition(pos);
	}
	void update() override {
		this->translate(0, - SPEED * G::dt);
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

		void onMouseClick(Mouse::Btn btn, Action action) override {
			if (action != Action::DOWN) return; // skip up actions
			if (btn == Mouse::Btn::LEFT) {
				Game::inst().scene->addChild(new Projectile(this->pos));
				std::cout << "pew" << std::endl;
			}
		}
		// void onKeyPress(int key, Input::Action action) override {
		// 	if (key == GLFW_KEY_RIGHT) {
		// 		this->translate(speed * G::dt, 0);
		// }
		void update() override {
			// std::cout << Mouse::pos().getX() << std::endl;
			this->setPosition(
				Mouse::pos().getX() - this->getWidth() / 2,
				Mouse::pos().getY() + this->getHeight() / 2 - 10);

		// 	if (Kb::down(Kb::Key::UP) && Kb::down(Kb::Key::RIGHT)) {
		// 		this->translate(speed * G::dt, speed * G::dt * -1);
		// 	} 
		// 	else if (Kb::down(Kb::Key::UP) && Kb::down(Kb::Key::LEFT)) {
		// 		this->translate(speed * G::dt * -1, speed * G::dt * -1);
		// 	} 
		// 	else if (Kb::down(Kb::Key::DOWN) && Kb::down(Kb::Key::RIGHT)) {
		// 		this->translate(speed * G::dt, speed * G::dt);
		// 	} 
		// 	else if (Kb::down(Kb::Key::DOWN) && Kb::down(Kb::Key::LEFT)) {
		// 		this->translate(speed * G::dt * -1, speed * G::dt);
		// 	} 
		// 	else if (Kb::down(Kb::Key::RIGHT)) {
		// 		this->translate(speed * G::dt, 0);
		// 	} 
		// 	else if (Kb::down(Kb::Key::LEFT)) {
		// 		this->translate(-(speed * G::dt), 0);
		// 	}
		// 	else if (Kb::down(Kb::Key::UP)) {
		// 		this->translate(0, -(speed * G::dt));
		// 	}
		// 	else if (Kb::down(Kb::Key::DOWN)) {
		// 		this->translate(0, (speed * G::dt));
		// 	}
		}
};


int main() {
	Game game(1200, 700, "8 Way Movement");
	game.scene->addChild(new KeyHandler());
	game.scene->addChild(new Player());
	// game.scene->addChild(new Triangle(Position(10, 100), Point(50, 0), Point(90, 100), Color::BLACK));
	game.run();
}