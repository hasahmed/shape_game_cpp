#include "shapegame.hpp"
using namespace shapegame;
int main() {
	Game game(800, 800, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(std::make_unique<DebugKeyHandler>());
	Triangle* t = game.scene->addChildAs<Triangle>(std::make_unique<Triangle>(Point(100, 50), Point(200, 10), Point(86, 200) , Color::BLACK));
	Square* s = game.scene->addChildAs<Square>(std::make_unique<Square>(Point(10, 10), 10, Color::YELLOW));
	// Square* s = game.scene->addChildAs<Square>(std::make_unique<Square>(Point(10, 10), 620, Color::YELLOW));
	std::unique_ptr<Square> newSquare = std::make_unique<Square>(Point(10, 10), 10, Color::GREEN);
	newSquare->translate(100, 0);


	// std::unique_ptr<Square> s = std::make_unique<Square>(Point(10, 10), 100, Color::YELLOW);
	// s->addShape(std::move(newSquare));


	int has_scaled = 0;
	// std::cout << t->getHeight() << std::endl;
		// std::cout << s->getSize() << std::endl;
	game.scene->addChild(new Timer(2000, true, true, [&t, &s, &has_scaled]{
		// t->scaleX(2);
		// t->scaleY(2);
		// if (has_scaled == 0) {
		// 	s->setScale(Point(2, 1));
		// }
		// else {
		// 	s->setScale(Point(1, 1));
		// }
		s->setScale(Point(2, 2));
		std::cout << s->getScale() << std::endl;
		std::cout << s->getSize() << std::endl;
		// t->scaleY(1.1);
		// std::cout << s->getHeight() << std::endl;
		// std::cout << s->getWidth() << std::endl;
		// std::cout << s->getShapes()[0]->getSize() << std::endl;
		// t->setScale(Point(2, 2));
		// std::cout << t->getWidth() << std::endl;
	}));

	// std::cout << t->getWidth() << std::endl;
	// std::cout << t->getHeight() << std::endl;

	game.run();
}