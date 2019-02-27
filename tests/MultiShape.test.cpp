#include <assert.h>
#include <memory>
#include <string>
#include <iostream>
#include "../shapegame"

using namespace shapegame;

#define KILL_UP 100
#define KILL_DOWN -100

enum Direction {
	UP = -1,
	DOWN = 1
};

class CarComponent : public Component {
	private:
		Point minMaxSpeed;
		float speed = 0;
		Direction dir = Direction::UP;
	public:
		void setDirection(Direction dir) {
			this->dir = dir;
		}
		void setSpeed(float speed) {
			this->speed = speed;
		}
		CarComponent(
			Direction dir = Direction::UP,
			Point minMaxSpeed = Point(100, 200)
		): minMaxSpeed(minMaxSpeed), dir(dir)  {
			int minSpeed = floor(minMaxSpeed.getX());
			int maxSpeed = floor(minMaxSpeed.getY());
			this->speed = (rand() % minSpeed) + maxSpeed;
		}
		void update(Entity *ent) override {
			ent->translate(0, speed * this->dir * 10);
			if (ent->pos.getY() < KILL_UP || ent->pos.getY() > KILL_DOWN) ent->kill();
		}
};

class TwoRects : public MultiShape {
	public:
	TwoRects(Position pos): MultiShape(pos) {
		this->addShape(new Rectangle(100, 100, pos, Color::BLACK));
		this->addShape(new Rectangle(100, 100, Position(pos.getX() + 200, pos.getY()), Color::BLACK));
	}
};


class CarTri : public TriangleIsosceles {
	public:
	CarTri(Position pos): TriangleIsosceles(100, 100, pos, Color::BLACK) {
		this->addComponent(new CarComponent());
	}
	void onKill() override {
		// std::cout << "CarTri Killed" << std::endl;
	}
};

#define SIZE 10000

std::multimap<unsigned int, std::unique_ptr<Object>> mm;

int main(){
	// new Position(100, 100);
	for (int i = 0; i < SIZE; i++) {
		mm.insert({
			1,
			std::unique_ptr<Object>(new CarTri(Position(100, 100)))
		});
	}
	std::cout<<  "Erased: " << mm.erase(1) << std::endl;
	// getchar();
	// for (int i = 0; i < SIZE; i++) {
	// 	delete ptrs[i];
	// }
}