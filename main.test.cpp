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

class Quad : public MultiShape {
	public:
	Quad(Position p1, Point p2, Point p3, Point p4, Color color) : MultiShape(p1) {
		auto t1 = new Triangle(p1, p2, p3);
		auto t2 = new Triangle(p1, p3, p4);


		this->addShape(t1);
		this->addShape(t2);
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
		this->setZOrder(1);
		// this->zOrder = 1;

		auto mid = new Rectangle(20, 10, pos, color);
		mid->setPosition(mid->pos.getX() + 10, mid->pos.getY() -10);

		auto left = new Triangle(Position(0, 0), Point(5, 0), Point(5, 10), color);
		left->setPosition(pos);
		left->translate(5, -10);

		auto right = new Triangle(Position(0, 0), Point(5, 0), Point(0, 10), color);
		right->setPosition(pos);
		right->translate(30, -10);

		this->addShape(mid);
		this->addShape(left);
		this->addShape(right);
	}
};

class TaxyBase: public MultiShape {
	public:
	TaxyBase(Position pos): MultiShape(pos) {
		int carWidth = 40;
		int carLength = 90;
		auto body = new Rectangle(carWidth , carLength, pos, Color::YELLOW);
		auto hood = new Rectangle(20, 10, pos, Color::YELLOW);
		hood->setPosition(hood->pos.getX() + 10, hood->pos.getY() -10);

		auto hoodLeft = new Triangle(Position(0, 0), Point(10, -10), Point(10, 0), Color::YELLOW);
		hoodLeft->setPosition(pos);
		// hoodLeft->translate(0, 0);

		auto hoodRight = new Triangle(Position(0, 0), Point(0, -10), Point(10, 0), Color::YELLOW);
		hoodRight->setPosition(pos);
		hoodRight->translate(30, 0);

		auto windShield = new WindShield(pos);
		windShield->translate(0, 25);

		auto topThing = new Rectangle(25, 6, pos, Color::WHITE);
		topThing->translate(7, 35);
		topThing->setZOrder(1);

		auto leftWheel = new Rectangle(2, 15, pos, Color::BLACK);
		leftWheel->translate(-2, 5);

		auto leftBackWheel = new Rectangle(2, 15, pos, Color::BLACK);
		leftBackWheel->translate(-2, 65);

		auto rightWheel = new Rectangle(2, 15, pos, Color::BLACK);
		rightWheel->translate(carWidth, 5);

		auto rightBackWheel = new Rectangle(2, 15, pos, Color::BLACK);
		rightBackWheel->translate(carWidth, 65);

		this->shapes.push_back(leftBackWheel);
		this->shapes.push_back(rightBackWheel);
		this->shapes.push_back(rightWheel);
		this->shapes.push_back(leftWheel);
		this->shapes.push_back(windShield);
		this->shapes.push_back(body);
		this->shapes.push_back(hood);
		this->shapes.push_back(hoodRight);
		this->shapes.push_back(hoodLeft);
		this->shapes.push_back(topThing);
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
	// g.scene->addChild(new TaxyBase(Position(100, 100)));
	// g.scene->addChild(new WindShield(Position(100, 100)));

	auto q = g.scene->addChildAs<Quad>(new Quad(
		Position(0, 0),
		Point(50, -100),
		Point(100, -100),
		Point(150, 0),
		Color::BLACK
	));
	q->setPosition(100, 200);


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