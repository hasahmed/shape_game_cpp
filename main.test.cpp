#include "shapegame"
#include <vector>
using namespace shapegame;

class Box : public MultiShape {
	public:
	Box(Position pos): MultiShape(pos) {
		auto top = new Rectangle(100, 10, pos, Color::BLACK);
		auto left = new Rectangle(10, 100, pos, Color::BLACK);

		this->addShape(top);
		this->addShape(left);
	}
};

int main() {

	Game g(1200, 700, "Multi Test");
	// auto x = g.scene->addChildAs<DebugKeyHandler>(new DebugKeyHandler());
		// g.scene->addChild(new Rectangle(10, 100, Position(100, 100), Color::BLACK));
	// auto x = g.scene->addChildAs<Box>(new Box(Position(100, 100)));
	auto x = g.scene->addChild(std::make_unique<Box>(Position(100, 100)));
	x->kill();
	g.run();
}