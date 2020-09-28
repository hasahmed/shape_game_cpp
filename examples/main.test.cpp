#include "shapegame.hpp"
using namespace shapegame;
int main() {
	Game game(400, 400, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(std::make_unique<DebugKeyHandler>());
	Triangle* t = game.scene->addChildAs<Triangle>(std::make_unique<Triangle>(Point(100, 50), Point(200, 10), Point(86, 200) , Color::BLACK));
	Square* s = game.scene->addChildAs<Square>(std::make_unique<Square>(Point(10, 10), 100, Color::YELLOW));
	std::unique_ptr<Square> newSquare = std::make_unique<Square>(Point(10, 10), 100, Color::GREEN);
	newSquare->translate(100, 0);

	s->addShape(std::move(newSquare));

	// game.scene->addChild(std::move(newSquare));

	game.scene->addChild(new Timer(2000, true, true, [&t, &s]{
		// t->scaleX(2);
		// t->scaleY(2);
		// t->scaleY(1.1);
		t->setScale(Point(1, 2));
		std::cout << s->getShapes()[0]->getWidth() << std::endl;
		// std::cout << t->getHeight() << std::endl;
		// std::cout << t->getWidth() << std::endl;
	}));

	// std::cout << t->getWidth() << std::endl;
	// std::cout << t->getHeight() << std::endl;

	game.run();
}