#include "shapegame"
#include <vector>
using namespace shapegame;

class TriangleEqualateral : public Triangle {
	public:
	TriangleEqualateral(float width, float height, Position pos, Color color) :
		Triangle(Point(0, 0), Point(width / 2, -height), Point(width, 0), color) {
			this->setPosition(pos);
		}
};

int main() {

	Game g;
	g.scene->addChild(new DebugKeyHandler());
	auto x = new TriangleEqualateral(100, 100, Position(100, 200), Color::BLACK);
	auto y = new TriangleEqualateral(10, 10, Position(100, 200), Color::BLACK);
	auto shapes = std::vector<Shape*> { y };
	// g.scene->addChild(new TriangleEqualateral(100, 100, Position(100, 200), Color::BLACK));
	// g.scene->addChild(new TriangleEqualateral(10, 100, Position(300, 200), Color::GREEN));
	auto m = new MultiShape(x, shapes);

	// std::cout << "M" << std::endl;
	// std::cout << *m;
	g.scene->addChild(m);
	g.run();
}