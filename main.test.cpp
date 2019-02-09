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

class Car : public MultiShape {
	private:
	int speed = 0;
	public:
	Car(Position pos, int speed = 200): MultiShape(pos), speed(speed) {
		this->shapes.push_back(new Rectangle(50, 100, pos, Color::WHITE));
	}
	void update() override {
		this->setPosition(this->pos.getX(), (this->pos.getY() - speed * G::dt));
		if (this->pos.getY() < KILL_Y || this->pos.getY() > KILL_Z) this->kill();
	}
	void onKill() override {
	}
};

class CarSpawner : public Object {
	public:
	int intervalMs = 0;
	Timer *t = nullptr;
	CarSpawner(Position pos, int intervalMs = 500): 
		Object(pos),
		intervalMs(intervalMs) {
			t = new Timer(intervalMs, true, true, [](){
			std::cout << "here" << std::endl;
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


	Game g(1200, 700, "Road Way");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	auto leftRoadLines = new RoadLines(
		Point(15, - LINE_HEIGHT / 2),
		Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2),
		Point(6, 10)
	);
	g.scene->addChild(leftRoadLines);
	std::vector<float> leftRoadLanesX = leftRoadLines->getLanesX();
	printVect<float>(&leftRoadLanesX);
	// g.scene->addChild(new RoadLines(Point(15, -1000), Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 100)));
	g.scene->addChild(new MidLine(Point((SCREEN_WIDTH / 2) - ((LINE_WIDTH * 3) / 2), 0)));
	g.scene->addChild(new RoadLines(Point(695, - LINE_HEIGHT / 2) , Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 10)));
	for (auto lane : leftRoadLanesX) {
		auto c = new Car(Position(lane + 25, 600));
		g.scene->addChild(c);
	}
	g.scene->addChild(new CarSpawner(Position(0, 0)));
	// auto c = new Car(Position(40, 600));
	// g.scene->addChild(c);
	// bool killed = false;
	// g.scene->addChild(new Timer(0, true, true, [=]() mutable {
	// 	if (!killed) {
	// 		if (c->pos.getY() < 100){
	// 			c->kill();
	// 			killed = true;
	// 		}
	// 	}
	// }));
	

	g.run();
}