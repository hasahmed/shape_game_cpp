#include "shapegame"
#include <vector>
using namespace shapegame;


int main() {

	Game g(1200, 700, "Multi Test");
	g.scene->addChild(new DebugKeyHandler());
	g.run();
}