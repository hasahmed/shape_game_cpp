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

enum Direction {
	UP = -1,
	DOWN = 1
};

class Car : public Object {
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
	): Object(pos), minMaxSpeed(minMaxSpeed), dir(dir) {
		int minSpeed = floor(this->minMaxSpeed.getY());
		this->speed = (rand() % minSpeed) + this->minMaxSpeed.getX();
		if (base) {
			this->shapes.push_back(base);
		} else {
			this->shapes.push_back(new Rectangle(50, 100, pos, color));
		}
	}
	void update() override {
		this->translate(0, speed * this->dir * G::dt);
		if (this->pos.getY() < KILL_Y || this->pos.getY() > KILL_Z) this->kill();
	}
};

class WindShield : public MultiShape {
	public:
	WindShield(Position pos): WindShield(30, 10, pos, 3) {}
	WindShield(float width, float height, Position pos, float flair): MultiShape(pos) {
		this->setZOrder(1);
		auto q = new Quad(
			Position(0, 0),
			Point(-flair, -height),
			Point(width + flair, -height),
			Point(width, 0),
			Color::BLUE_LIGHT
		);
		q->setPosition(pos);
		this->addShape(q);
	}
};

class CarBase : public MultiShape {
	public:
	CarBase(float width, float length, Point flair, Point flairHeight, Position pos, Color color): MultiShape(pos) {
		auto bodyLength = length - flairHeight.getX() - flairHeight.getX();
		auto body = new Rectangle(width, bodyLength, pos, color);


		auto front = new Quad(
			Position(0, 0),
			Point(flair.getX(), -flairHeight.getX()),
			Point(width - flair.getX(), -flairHeight.getX()),
			Point(width, 0),
			color
		);
		auto back = new Quad(
			Position(0, 0),
			Point(flair.getY(), flairHeight.getY()),
			Point(width - flair.getY(), flairHeight.getY()),
			Point(width, 0),
			color
		);


		body->setPosition(pos);
		front->setPosition(pos);
		back->setPosition(pos);
		back->translate(0, bodyLength);


		this->addShape(body);
		this->addShape(front);
		this->addShape(back);
	}
};

class TaxiBase: public MultiShape {
	public:
	TaxiBase(Position pos): MultiShape(pos) {
		int carWidth = 40;
		int carLength = 90;
		auto body = new CarBase(carWidth, carLength, Point(10, 3), Point(8, 5), Position(100, 100), Color::YELLOW);

		auto windShield = new WindShield(pos);
		windShield->translate(5, 25);

		auto topThing = new Rectangle(25, 6, pos, Color::WHITE);
		topThing->translate(7, 35);
		topThing->setZOrder(1);

		auto leftWheel = new Rectangle(2, 15, pos, Color::BLACK);
		leftWheel->translate(-2, 5);

		auto leftBackWheel = new Rectangle(2, 15, pos, Color::BLACK);
		leftBackWheel->translate(-2, 55);

		auto rightWheel = new Rectangle(2, 15, pos, Color::BLACK);
		rightWheel->translate(carWidth, 5);

		auto rightBackWheel = new Rectangle(2, 15, pos, Color::BLACK);
		rightBackWheel->translate(carWidth, 55);

		this->shapes.push_back(leftBackWheel);
		this->shapes.push_back(rightBackWheel);
		this->shapes.push_back(rightWheel);
		this->shapes.push_back(leftWheel);
		this->shapes.push_back(windShield);
		this->shapes.push_back(body);
		this->shapes.push_back(topThing);
	}
};

// class Taxi : public Car {
// 	public:
// 	Taxi(Position pos, Direction dir = Direction::UP, Point minMaxSpeed = Point(100, 200), Color color = Color::YELLOW):
// 		Car(pos, dir, minMaxSpeed, color, new TaxiBase(pos)) {
// 		}
// };
class Taxi : public TaxiBase {
	public:
	Taxi(Position pos): TaxiBase(pos) {
	}
	void update() override {
		this->translate(0, 1);
	}
};

// class CarSpawner : public Object {
// 	public:
// 	int intervalMs = 0;
// 	Timer *t = nullptr;
// 	private:
// 	Direction dir = Direction::UP;
// 	public:
// 	CarSpawner(Position pos, Direction dir = Direction::UP, int intervalMs = 1000): 
// 		Object(pos),
// 		intervalMs(intervalMs),
// 		dir(dir) {
// 			t = new Timer(intervalMs, true, true, [=](){
// 				// Game::inst().scene->addChild(new Taxi(this->pos, this->dir));
// 				Game::inst().scene->addChild(new Taxi(this->pos));
// 			});
// 			Game::inst().scene->addChild(this->t);
// 		}
// };

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
	// g.scene->addChild(new TaxiBase(Position(100, 100)));
	// g.scene->addChild(new WindShield(Position(100, 100)));
	// g.scene->addChild(new CarBase(200, 100, Point(-10, 3), Point(50, 50), Position(100, 100), Color::BLACK));
	// g.scene->addChild(new CarBase(40, 100, Point(10, 3), Point(8, 5), Position(100, 100), Color::YELLOW));


	/**
	 * 
	 */



	auto leftRoadLines = new RoadLines(
		Point(15, - LINE_HEIGHT / 2),
		Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
		Point(6, 10)
	);
	auto rightRoadLines = new RoadLines(
		Point(695, - LINE_HEIGHT / 2),
		Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
		Point(6, 10)
	);
	g.scene->addChild(leftRoadLines);
	g.scene->addChild(rightRoadLines);
	std::vector<float> leftRoadLanesX = leftRoadLines->getLanesX();
	std::vector<float> rightRoadLanesX = rightRoadLines->getLanesX();
	g.scene->addChild(new MidLine(Point((SCREEN_WIDTH / 2) - ((LINE_WIDTH * 3) / 2), 0)));
	g.scene->addChild(new Taxi(Position(100, 100)));
	// for (auto lane : leftRoadLanesX) {
	// 	g.scene->addChild(new CarSpawner(Position(lane + 25, -300), Direction::DOWN));
	// }
	// for (auto lane : rightRoadLanesX) {
	// 	g.scene->addChild(new CarSpawner(Position(lane - 70, 800)));
	// }
	g.run();
}