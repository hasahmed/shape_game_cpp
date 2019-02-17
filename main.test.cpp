#include "shapegame"
#include <vector>
using namespace shapegame;

class Box : public MultiShape {
	public:
	Box(Position pos): MultiShape(pos) {
		auto top = new Rectangle(100, 10, pos, Color::BLACK);
		auto left = new Rectangle(10, 100, pos, Color::BLACK);
		this->shapes.push_back(top);
		this->shapes.push_back(left);
	}
};

int main() {

	Game g(1200, 700, "Multi Test");
	auto x = g.scene->addChildAs<DebugKeyHandler>(new DebugKeyHandler());
	auto box = g.scene->addChildAs<Box>(new Box(Position(100, 100)));
	box->kill();

	g.run();
}