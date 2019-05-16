#include "shapegame"
using namespace shapegame;



int main() {

	Game g(1200, 800, "Busy Highway");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(std::make_unique<DebugKeyHandler>());
	// g.scene->addChild(std::make_unique<Triangle>(Position(100, 100), Point(500, 300), Point(50, 300)));
	auto x = g.scene->addChild(std::make_unique<Rectangle>(100, 100, Position(100, 500), Color::BLUE));
	x->kill();
	// auto rect = std::make_unique<Rectangle>(100, 100, Position(100, 500), Color::BLUE);
	g.run();
}