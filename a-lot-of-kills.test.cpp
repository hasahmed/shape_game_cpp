#include "shapegame"
#include <vector>
#include <random>
using namespace shapegame;


#define LINE_WIDTH 3
#define LINE_HEIGHT 40
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define KILL_UP 100
#define KILL_DOWN 1200
#define BASE_CAR_WIDTH 40
#define BASE_CAR_LENGTH 90
#define BASE_FLAIR Point(10, 3)
#define BASE_FLAIR_HEIGHT Point(8, 5)

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
			ent->translate(0, speed * this->dir * G::dt);
			if (ent->pos.getY() < KILL_UP || ent->pos.getY() > KILL_DOWN) ent->kill();
		}
};
template <class T>
class Spawner: public Object {
	public:
	Spawner(Position pos, unsigned int intervalMs): Object(pos) {
		Game::inst().scene->addChild(new Timer(intervalMs, true, true, [=](){
			Game::inst().scene->addChild(new T(pos));
		}));
	}
};

template <typename T>
void printVect(std::vector<T> *vect) {
	std::cout << "[";
	for (auto ele : *vect) {
		std::cout << ele << ", ";
	}
	std::cout << "]" << std::endl;
}

class T : public TriangleIsosceles {
	public:
	T(Position pos): TriangleIsosceles(40, 40, pos, Color::PURPLE) {
		this->kill();
		// this->addComponent(new CarComponent);
	}
	// void update() override {
	// 	this->translate(0, -10);
	// 	if (this->pos.y < KILL_UP) this->kill();
	// }
};

int main() {


	Game g(1200, 700, "Busy Highway");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	// g.scene->addChild(new Spawner<T>(Position(600, 500), 0));
	#define NUM_OBJ 32
	#define WAIT_TIME 0
	// #define NUM_OBJ 10
	// Object *ov[NUM_OBJ];

	g.scene->addChild(new Timer(WAIT_TIME , true, true, [&g]() mutable {
		std::cout << "Children: " << g.scene->numChildren() << std::endl;
		std::cout << "Adding children" << std::endl;
		for (int i = 0; i < NUM_OBJ ; i++) {
			auto x = new TriangleIsosceles(100, 100, Position(500, 500), Color::BLACK);
			g.scene->addChild(x);
			x->kill();
		}
		// std::cout << "Children: " << g.scene->numChildren() << std::endl;
		// g.scene->addChild(new Timer(WAIT_TIME, false, true, [&ov, &g](){
		// 	std::cout << "killing" << std::endl;
		// 	for (int i = 0; i < NUM_OBJ; i++) {
		// 		ov[i]->kill();
		// 		// std::cout << ov[i] << std::endl;
		// 	}
		// 	std::cout << "Children: " << g.scene->numChildren() << std::endl;
		// }));
	}));
	// g.scene->addChild(new T(Position(600, 500)));
	g.run();
}