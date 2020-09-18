#include "shapegame.hpp"
using namespace shapegame;
int main() {
	Game game(400, 400, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(std::make_unique<DebugKeyHandler>());
	Triangle* t = game.scene->addChildAs<Triangle>(std::make_unique<TriangleIsosceles>(100, 100, Position(100, 101), Color::BLACK));

	game.scene->addChild(new Timer(2000, true, true, [&t]{
		// t->scaleX(2);
		// t->scaleY(2);
		// t->scaleY(1.1);
		t->setScale(Point(1, 2));
	}));

	game.run();
}