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

class RoadLine : public Rectangle {
	public:
	RoadLine(Position pos, Point size = Point(LINE_WIDTH, LINE_HEIGHT), Color color = Color::WHITE):
		Rectangle(size.getX(), size.getY(), pos, color) {}
};

class MidLine : public MultiShape {
	public:
	MidLine(Position pos): MultiShape(pos) {
		this->shapes.push_back(
			(Shape*)
			new RoadLine(pos, Point(LINE_WIDTH, SCREEN_HEIGHT), Color::YELLOW)
		);
		this->shapes.push_back(
			(Shape*)
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
					(Shape*)
					new RoadLine(Position(pos.getX() + x * freq.getX(), pos.getY() + y * freq.getY()))
				);
			}
		}
	}
	void update() override {
		// std::cout << (Shape&) *(this->pos.owner_) << std::endl;
		// this->setPosition(0, 0);
		// this->translate(0, 1);
	}
};

int main() {


	Game g(1200, 700, "Road Way");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	// auto x = new TriangleIsosceles(100, 100, Position(0, 200), Color::BLACK);
	// auto y = new TriangleIsosceles(100, 100, Position(100, 200), Color::RED);
	// auto z = new TriangleIsosceles(100, 100, Position(200, 200), Color::GREEN);
	// auto a = new TriangleIsosceles(100, 100, Position(300, 200), Color::PINK);
	// auto shapes = std::vector<Shape*> { x, y, z, a };
	// auto m = new MultiShape(x, shapes);
	// Rectangle *r = new Rectangle(100, 300, Position(10, 10), Color::GREEN);
	// g.scene->addChild(r);
	// g.scene->addChild(new RoadLine(Point(10, 10)));
	g.scene->addChild(new RoadLines(Point(15, - LINE_HEIGHT / 2), Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 10)));
	g.scene->addChild(new MidLine(Point((SCREEN_WIDTH / 2) - ((LINE_WIDTH * 3) / 2), 0)));
	g.scene->addChild(new RoadLines(Point(695, - LINE_HEIGHT / 2) , Point(98, LINE_HEIGHT * 2 + LINE_HEIGHT / 2), Point(6, 10)));
	// g.scene->addChild(new RoadLines(Point(, 10), Point(100, 10), Point(6, 10)));

	// g.scene

	// g.scene->addChild(m);
	// m->setPosition(100, 100);
	// g.scene->addChild(new Timer(0, true, true, [=]{
	// 	m->setPosition(m->pos.getX() + 1, m->pos.getY());
	// }));
	g.run();
}