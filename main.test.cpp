#include "shapegame"
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

	Game g(1200, 700, "Road Way");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	// auto x = new TriangleIsosceles(100, 100, Position(0, 200), Color::BLACK);
	// auto y = new TriangleIsosceles(100, 100, Position(100, 200), Color::RED);
	// auto z = new TriangleIsosceles(100, 100, Position(200, 200), Color::GREEN);
	// auto a = new TriangleIsosceles(100, 100, Position(300, 200), Color::PINK);
	// auto shapes = std::vector<Shape*> { x, y, z, a };
	// auto m = new MultiShape(x, shapes);
	Rectangle *r = new Rectangle(100, 300, Position(10, 10), Color::GREEN);
	g.scene->addChild(r);

	// g.scene

	// g.scene->addChild(m);
	// m->setPosition(100, 100);
	// g.scene->addChild(new Timer(0, true, true, [=]{
	// 	m->setPosition(m->pos.getX() + 1, m->pos.getY());
	// }));
	g.run();
}