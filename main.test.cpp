#include "shapegame"
#include <map>
#include <map>
#include <vector>
#include <random>
using namespace shapegame;


#define LINE_WIDTH 3
#define LINE_HEIGHT 40
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define KILL_UP - 400
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

class Steerable : public Component {
	public:
	void update(Entity *ent) override {
		if (Input::Kb::down(Input::Kb::Key::RIGHT))
			ent->translate(100 * G::dt, 0);
		if (Input::Kb::down(Input::Kb::Key::LEFT))
			ent->translate(-1 * 100 * G::dt, 0);
	}
};

class WindShield : public MultiShape {
	public:
	WindShield(Position pos): WindShield(30, 10, pos, 3) {}
	WindShield(float width, float height, Position pos, float flair): MultiShape(pos) {
		// this->setZOrder(1);
		auto q = std::make_unique<Quad>(
			Position(0, 0),
			Point(-flair, -height),
			Point(width + flair, -height),
			Point(width, 0),
			Color::BLUE_LIGHT
		);
		q->setPosition(pos);
		this->addShape(std::move(q));
	}
};

class CarBase : public MultiShape {
	public:
	CarBase(float width, float length, Point flair, Point flairHeight, Position pos, Color color): MultiShape(pos) {
		auto bodyLength = length - flairHeight.getX() - flairHeight.getX();
		auto body = std::make_unique<Rectangle>(width, bodyLength, pos, color);

		auto front = std::make_unique<Quad>(
			Position(0, 0),
			Point(flair.getX(), -flairHeight.getX()),
			Point(width - flair.getX(), -flairHeight.getX()),
			Point(width, 0),
			color
		);
		auto back = std::make_unique<Quad>(
			Position(0, 0),
			Point(flair.getY(), flairHeight.getY()),
			Point(width - flair.getY(), flairHeight.getY()),
			Point(width, 0),
			color
		);

		auto windShield = std::make_unique<WindShield>(pos);
		windShield->translate(5, 25);
		auto leftWheel = std::make_unique<Rectangle>(2, 15, pos, Color::BLACK);
		leftWheel->translate(-2, 5);

		auto leftBackWheel = std::make_unique<Rectangle>(2, 15, pos, Color::BLACK);
		leftBackWheel->translate(-2, 55);

		auto rightWheel = std::make_unique<Rectangle>(2, 15, pos, Color::BLACK);
		rightWheel->translate(width, 5);

		auto rightBackWheel = std::make_unique<Rectangle>(2, 15, pos, Color::BLACK);
		rightBackWheel->translate(width, 55);



		body->setPosition(pos);
		front->setPosition(pos);
		back->setPosition(pos);
		back->translate(0, bodyLength);


		this->addShape(std::move(body));
		this->addShape(std::move(front));
		this->addShape(std::move(back));
		this->addShape(std::move(leftBackWheel));
		this->addShape(std::move(rightBackWheel));
		this->addShape(std::move(rightWheel));
		this->addShape(std::move(leftWheel));
		this->addShape(std::move(windShield));
	}
};

class Car : public CarBase {
	public:
	// using CarBase::CarBase;
		Car(Position pos, Color color, Direction dir = Direction::UP): CarBase(
			BASE_CAR_WIDTH,
			BASE_CAR_LENGTH,
			BASE_FLAIR,
			BASE_FLAIR_HEIGHT,
			pos,
			color) {
				auto cc = std::make_unique<CarComponent>();
				cc->setDirection(dir);
				this->addComponent(std::move(cc));
				this->addComponent(std::make_unique<Steerable>());
		}
};
class Taxi : public Car {
	public:
	Taxi(Position pos): Car(pos, Color::YELLOW) {
		auto topThing = std::make_unique<Rectangle>(25, 6, pos, Color::WHITE);
		topThing->translate(7, 35);
		this->addShape(std::move(topThing));
	}
	void onAdd() override {
	}
	void onKill() override {
		// std::cout << "killd" << std::endl;
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
		this->addShape(
			std::make_unique<RoadLine>(pos, Point(LINE_WIDTH, SCREEN_HEIGHT), Color::YELLOW)
		);
		this->addShape(
			std::make_unique<RoadLine>(Position(pos.getX() + (LINE_WIDTH * 2), pos.getY()), Point(3, 1000), Color::YELLOW)
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
				this->addShape(
					std::make_unique<RoadLine>(Position(pos.getX() + x * freq.getX(), pos.getY() + y * freq.getY()))
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

int i = 0;

template <class T>
class Spawner: public Object {
	private:
	Timer *t;
	public:
	Spawner(Position pos, unsigned int intervalMs): Object(pos) {
		this->t = (Timer*) Game::inst().scene->addChild(std::make_unique<Timer>(intervalMs, true, true, [=]() mutable {
			i++;
			// std::cout << "Car spawned: " << i << std::endl;
			// auto x = std::make_unique<T>(pos);
			// Game::inst().scene->addChild(std::move(x));
			Game::inst().scene->shouldCheck = true;
			Game::inst().scene->queueAddChild(std::make_unique<DebugKeyHandler>());
		}, false));
	}
	void onMouseClick(Mouse::Btn btn, Input::Action action) override {
		this->t->stop();
		this->kill();
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

class CarTri : public TriangleIsosceles {
	public:
	CarTri(Position pos): TriangleIsosceles(100, 100, pos, Color::BLACK) {
		this->addComponent(std::make_unique<CarComponent>());
	}
	void onKill() override {
		// std::cout << "CarTri Killed" << std::endl;
	}
};

int main() {


	Game g(1200, 800, "Busy Highway");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(std::make_unique<DebugKeyHandler>());



	auto leftRoadLines = std::make_unique<RoadLines>(
		Point(15, - LINE_HEIGHT / 2),
		Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
		Point(6, 10)
	);
	auto rightRoadLines = std::make_unique<RoadLines>(
		Point(695, - LINE_HEIGHT / 2),
		Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
		Point(6, 10)
	);
	auto rawLeftRoadLines = leftRoadLines.get();
	auto rawRightRoadLines = leftRoadLines.get();
	g.scene->addChild(std::move(leftRoadLines));
	g.scene->addChild(std::move(rightRoadLines));
	std::vector<float> leftRoadLanesX =  rawLeftRoadLines->getLanesX();
	std::vector<float> rightRoadLanesX = rawRightRoadLines->getLanesX();
	g.scene->addChild(std::make_unique<MidLine>(Point((SCREEN_WIDTH / 2) - ((LINE_WIDTH * 3) / 2), 0)));
	for (auto lane : leftRoadLanesX) {
		// g.scene->addChild(std::make_unique<Spawner<Taxi>>(Position(lane + 25, 1000), 500));
		g.scene->addChild(std::make_unique<Spawner<CarTri>>(Position(lane + 25, 1000), 500));
	}
	g.run();
}