/**
 * 8 WAY Character
 * 
 */
#include "shapegame.hpp"
#include <cstdlib>
using namespace shapegame;
using namespace shapegame::Input;

// class Projectile : public Rectangle {
class Projectile : public Triangle {
	public:
	const int SPEED = rand() % 100;
	Projectile(Position pos, Point size = Point(10, 50)):
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
		void update() override {
			this->setPosition(
				Mouse::pos().getX() - this->getWidth() / 2,
				Mouse::pos().getY() + this->getHeight() / 2 - 10);

		}
};


int main() {
	Game game(1200, 700, "8 Way Movement");
	game.scene->addChild(new DebugKeyHandler());
	game.scene->addChild(new Player());
	game.run();
}
