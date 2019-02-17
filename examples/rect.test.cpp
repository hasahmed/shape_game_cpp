#include "shapegame"
#include <vector>
#include <random>
using namespace shapegame;
int main() {

	Game g(1200, 700, "Kill Tests");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	auto rect = new Rectangle(100, 100, Position(100, 500), Color::WHITE);
	// auto tri = new TriangleIsosceles(100, 100, Position(500, 500), Color::WHITE);
	g.scene->addChild(rect);
	// rect->kill();
	// g.scene->addChild(tri);
	// tri->kill();
	g.run();
}