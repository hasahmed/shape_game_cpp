#include "shapegame"
using namespace shapegame;



int main() {

	Game g(1200, 800, "Busy Highway");
	g.scene->setBackgroundColor(Color::GRAY);
	g.scene->addChild(std::make_unique<DebugKeyHandler>());
	g.run();
}