#include "shapegame.hpp"
using namespace shapegame;


int main() {

	Game game(800, 800, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);

	game.scene->addChild(new DebugKeyHandler()); // escape key closes window, 1, 2, show traingles
	// game.scene->addChild(std::make_unique<Circle>(Position(5200, 500), 10000, 1000, Color::BLACK));
	// game.scene->addChild(std::make_unique<Circle>(Position(5200, 500), 10000, 300, Color::BLACK));
	int const start = 250;
	game.scene->addChild(std::make_unique<Circle>(Position(start, 250), 500, 3, Color::RED));
	game.scene->addChild(std::make_unique<Circle>(Position(start + 270, 500), 500, 4, Color::GREEN));
	// game.scene->addChild(std::make_unique<Circle>(Position(500, 500), 500, 500, Color::BLACK));

	game.run();
}
