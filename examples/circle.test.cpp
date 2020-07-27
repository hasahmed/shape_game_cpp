#include "shapegame.hpp"
using namespace shapegame;


int main() {

	Game game(800, 800, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);

	game.scene->addChild(new DebugKeyHandler()); // escape key closes window, 1, 2, show traingles
	game.scene->addChild(std::make_unique<Circle>(Position(500, 500), 500, 500, Color::BLACK));

	game.run();
}
