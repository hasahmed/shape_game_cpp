#include "shapegame"
#include <vector>
using namespace shapegame;


#define LINE_WIDTH 3
#define LINE_HEIGHT 40
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

class TriangleIsosceles : public Triangle {
	public:
	TriangleIsosceles(float width, float height, Position pos, Color color) :
		Triangle(Point(0, 0), Point(width / 2, -height), Point(width, 0), color) {
			this->setPosition(pos);
		}
};

class Car : public MultiShape {
	public:
	Car(Position pos): MultiShape(pos) {
		this->shapes.push_back(new Rectangle(50, 100, pos, Color::WHITE));
	}
	void update() override {
		this->setPosition(this->pos.getX(), (this->pos.getY() - 200 * G::dt));
		if (this->pos.getY() < 100) this->kill();
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
	public:
	RoadLines(Position pos, Point freq, Point amount): MultiShape(pos) {
		for (int x = 0; x < amount.getX(); x++) {
			for (int y = 0; y < amount.getY(); y++) {
				this->shapes.push_back(
					new RoadLine(Position(pos.getX() + x * freq.getX(), pos.getY() + y * freq.getY()))
				);
			}
		}
	}
	void update() override {
		// this->setPosition(this->pos.getX(), this->pos.getY() + 30 * G::dt);
	}
};

int main() {


	Game g(1200, 700, "Road Way");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	g.scene->addChild(new RoadLines(Point(15, - LINE_HEIGHT / 2), Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 10)));
	// g.scene->addChild(new RoadLines(Point(15, -1000), Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 100)));
	g.scene->addChild(new MidLine(Point((SCREEN_WIDTH / 2) - ((LINE_WIDTH * 3) / 2), 0)));
	g.scene->addChild(new RoadLines(Point(695, - LINE_HEIGHT / 2) , Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 10)));
	auto c = new Car(Position(40, 600));
	g.scene->addChild(c);
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