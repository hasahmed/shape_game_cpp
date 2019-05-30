#include "shapegame.hpp"
#include <vector>
using namespace shapegame;

class TriangleIsosceles : public Triangle {
	public:
	TriangleIsosceles(float width, float height, Position pos, Color color) :
		Triangle(Point(0, 0), Point(width / 2, -height), Point(width, 0), color) {
			this->setPosition(pos);
		}
	
	void onAdd() override {
		// std::cout << "ADDDDEDDDDD\n";
		// std::cout << *this << std::endl;
	}
};

int main() {

	Game g(1200, 700, "Multi Test");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	auto x = new TriangleIsosceles(100, 100, Position(0, 200), Color::BLACK);
	auto y = new TriangleIsosceles(100, 100, Position(100, 200), Color::RED);
	auto z = new TriangleIsosceles(100, 100, Position(200, 200), Color::GREEN);
	auto a = new TriangleIsosceles(100, 100, Position(300, 200), Color::PINK);
	// auto y = new TriangleIsosceles(10, 10, Position(100, 200), Color::BLACK);
	// auto shapes = std::vector<Shape*> { x, y, z };
	auto shapes = std::vector<Shape*> { x, y, z, a };
	// auto shapes = std::vector<Shape*> { x };
	// auto shapes = std::vector<Shape*> { y };
	// g.scene->addChild(new TriangleIsosceles(100, 100, Position(100, 200), Color::BLACK));
	// g.scene->addChild(new TriangleIsosceles(10, 100, Position(300, 200), Color::GREEN));
	auto m = new MultiShape(x, shapes);

	// std::cout << "M" << std::endl;
	// std::cout << *m;
	g.scene->addChild(m);
	m->setPosition(100, 100);
	g.scene->addChild(new Timer(0, true, true, [=]{
		// std::cout << "here" << std::endl;
		m->setPosition(m->pos.getX() + 1, m->pos.getY());
		// m->pos.setX(m->pos.getX() + 1);

	}));
	// g.scene->addChild(x);
	// g.scene->addChild(y);
	// g.scene->addChild(z);
	// g.scene->addChild(a);
	// g.scene->addChild(y);
	g.run();
}