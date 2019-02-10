#include "shapegame"
#include <vector>
#include <random>
using namespace shapegame;


#define LINE_WIDTH 3
#define LINE_HEIGHT 40
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define KILL_Y -1000
#define KILL_Z 2000

class TriangleIsosceles : public Triangle {
	public:
	TriangleIsosceles(float width, float height, Position pos, Color color) :
		Triangle(Point(0, 0), Point(width / 2, -height), Point(width, 0), color) {
			this->setPosition(pos);
		}
};

enum Direction {
	UP = -1,
	DOWN = 1
};

class Car : public MultiShape {
	private:
	Point minMaxSpeed;
	float speed = 0;
	Direction dir = Direction::UP;
	public:
	Car(
		Position pos,
		Direction dir = Direction::UP,
		Point minMaxSpeed = Point(100, 200),
		Color color = Color::WHITE,
		Object *base = nullptr
	): MultiShape(pos), minMaxSpeed(minMaxSpeed), dir(dir) {
		int minSpeed = floor(this->minMaxSpeed.getY());
		this->speed = (rand() % minSpeed) + this->minMaxSpeed.getX();
		if (base) {
			this->shapes.push_back(base);
		} else {
			this->shapes.push_back(new Rectangle(50, 100, pos, color));
		}
	}
	void update() override {
		this->setPosition(this->pos.getX(), (this->pos.getY() + speed * this->dir * G::dt));
		if (this->pos.getY() < KILL_Y || this->pos.getY() > KILL_Z) this->kill();
	}
};

class WindShield : public MultiShape {
	public:
	WindShield(Position pos): MultiShape(pos) {
		Color color = Color::BLUE;

		auto mid = new Rectangle(20, 10, pos, color);
		mid->setPosition(mid->pos.getX() + 10, mid->pos.getY() -10);

		auto left = new Triangle(Position(0, 0), Point(10, -10), Point(10, 0), color);
		left->setPosition(pos);
		// hoodLeft->translate(0, 0);

		auto right = new Triangle(Position(0, 0), Point(0, -10), Point(10, 0), color);
		right->setPosition(pos);
		right->translate(30, 0);


		this->shapes.push_back(mid);
		this->shapes.push_back(left);
		this->shapes.push_back(right);
	}
	void update() override {
		// this->translate(-0.1, 0);
	}
};

class TaxyBase: public MultiShape {
	public:
	TaxyBase(Position pos): MultiShape(pos) {
		auto body = new Rectangle(40, 90, pos, Color::YELLOW);
		auto hood = new Rectangle(20, 10, pos, Color::YELLOW);
		hood->setPosition(hood->pos.getX() + 10, hood->pos.getY() -10);

		auto hoodLeft = new Triangle(Position(0, 0), Point(10, -10), Point(10, 0), Color::YELLOW);
		hoodLeft->setPosition(pos);
		// hoodLeft->translate(0, 0);

		auto hoodRight = new Triangle(Position(0, 0), Point(0, -10), Point(10, 0), Color::YELLOW);
		hoodRight->setPosition(pos);
		hoodRight->translate(30, 0);

		auto windShield = new WindShield(pos);
		// windShield->translate(50, 20);
		// auto windSheild = new Rectangle(30, 15, pos, Color::BLUE);
		// windSheild->translate(5, 0);

		this->shapes.push_back(windShield);
		this->shapes.push_back(body);
		this->shapes.push_back(hood);
		this->shapes.push_back(hoodRight);
		this->shapes.push_back(hoodLeft);
	}
};

class Taxy : public Car {
	public:
	Taxy(Position pos, Direction dir = Direction::UP, Point minMaxSpeed = Point(100, 200), Color color = Color::YELLOW):
		Car(pos, dir, minMaxSpeed, color) {
		}
};

class CarSpawner : public Object {
	public:
	int intervalMs = 0;
	Timer *t = nullptr;
	private:
	Direction dir = Direction::UP;
	public:
	CarSpawner(Position pos, Direction dir = Direction::UP, int intervalMs = 1000): 
		Object(pos),
		intervalMs(intervalMs),
		dir(dir) {
			t = new Timer(intervalMs, true, true, [=](){
				Game::inst().scene->addChild(new Taxy(this->pos, this->dir));
			});
			Game::inst().scene->addChild(this->t);
		}
};

class RoadLine : public Rectangle {
	public:
	RoadLine(Position pos, Point size = Point(LINE_WIDTH, LINE_HEIGHT), Color color = Color::WHITE):
		Rectangle(size.getX(), size.getY(), pos, color) {}
};

class MidLine : public MultiShape {
	public:
	MidLine(Position pos): MultiShape(pos) {
		this->shapes.push_back(
			new RoadLine(pos, Point(LINE_WIDTH, SCREEN_HEIGHT), Color::YELLOW)
		);
		this->shapes.push_back(
			new RoadLine(Position(pos.getX() + (LINE_WIDTH * 2), pos.getY()), Point(3, 1000), Color::YELLOW)
		);
	}
};

class RoadLines : public MultiShape {
	private:
	Point freq;
	Point amount;
	public:
	RoadLines(Position pos, Point freq, Point amount): MultiShape(pos), freq(freq), amount(amount)  {
		for (int x = 0; x < amount.getX(); x++) {
			for (int y = 0; y < amount.getY(); y++) {
				this->shapes.push_back(
					new RoadLine(Position(pos.getX() + x * freq.getX(), pos.getY() + y * freq.getY()))
				);
			}
		}
	}
	std::vector<float> getLanesX(){
		std::vector<float> ret;
		for (int x = 0; x < this->amount.getX(); x++) {
			ret.push_back(this->pos.getX() + x * freq.getX());
		}
		return ret;
	}
	void update() override {
		// this->setPosition(this->pos.getX(), this->pos.getY() + 30 * G::dt);
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

int main() {


	Game g(1200, 700, "Busy Highway");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());

	/**
	 */
	g.scene->addChild(new TaxyBase(Position(100, 100)));

	/**
	 * 
	 */



	// auto leftRoadLines = new RoadLines(
	// 	Point(15, - LINE_HEIGHT / 2),
	// 	Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
	// 	Point(6, 10)
	// );
	// auto rightRoadLines = new RoadLines(
	// 	Point(695, - LINE_HEIGHT / 2),
	// 	Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
	// 	Point(6, 10)
	// );
	// g.scene->addChild(leftRoadLines);
	// g.scene->addChild(rightRoadLines);
	// std::vector<float> leftRoadLanesX = leftRoadLines->getLanesX();
	// std::vector<float> rightRoadLanesX = rightRoadLines->getLanesX();
	// g.scene->addChild(new MidLine(Point((SCREEN_WIDTH / 2) - ((LINE_WIDTH * 3) / 2), 0)));
	// for (auto lane : leftRoadLanesX) {
	// 	g.scene->addChild(new CarSpawner(Position(lane + 25, -300), Direction::DOWN));
	// }
	// for (auto lane : rightRoadLanesX) {
	// 	g.scene->addChild(new CarSpawner(Position(lane - 70, 800)));
	// }
	g.run();
}