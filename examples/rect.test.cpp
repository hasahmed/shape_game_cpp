#include "shapegame.hpp"
#include <vector>
#include <random>
using namespace shapegame;
int main() {

	Game g(1200, 700, "Kill Tests");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(new DebugKeyHandler());
	auto rect = new Rectangle(100, 100, Position(100, 500), Color::WHITE);
	g.scene->addChild(rect);
	g.run();
}
