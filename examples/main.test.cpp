#include "shapegame.hpp"
using namespace shapegame;
int main() {
	Game game(800, 800, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(std::make_unique<DebugKeyHandler>());
	Triangle* t = game.scene->addChildAs<Triangle>(std::make_unique<Triangle>(Point(100, 50), Point(200, 10), Point(86, 200) , Color::BLACK));
	Square* s = game.scene->addChildAs<Square>(std::make_unique<Square>(Point(600, 10), 10, Color::YELLOW));
	// Square* s = game.scene->addChildAs<Square>(std::make_unique<Square>(Point(10, 10), 620, Color::YELLOW));
	std::unique_ptr<Square> newSquare = std::make_unique<Square>(Point(10, 10), 10, Color::GREEN);
	newSquare->translate(100, 0);


	// std::unique_ptr<Square> s = std::make_unique<Square>(Point(10, 10), 100, Color::YELLOW);
	// s->addShape(std::move(newSquare));


	int has_scaled = 0;
	// std::cout << t->getHeight() << std::endl;
		// std::cout << s->getSize() << std::endl;
	game.scene->addChild(new Timer(1000, true, true, [&t, &s, &has_scaled]{
		// if (has_scaled == 0) {
		// 	s->setScale(Point(2, 2));
		// 	has_scaled = 1;
		// }
		// else {
		// 	// s->setScale(Point(1, 1));




		// if (has_scaled == 0) {
		// 	s->translate(100, 0);
		// }
		// if (has_scaled == 1) {
		// 	s->setScale(3);
		// }
		// if (has_scaled == 2) {
		// 	s->setScale(1);
		// }
		// if (has_scaled == 3) {
		// 	s->translate(-100, 0);
		// }
		// has_scaled++;




			s->setScale(3);
			// s->setScale(Point(s->getScale().x + 1, s->getScale().y + 1));
			// s->rotate(1);
			// s->setScale(s->getScale().x + 0.1);
			// if (has_scaled == 5) {
			// 	s->setScale(1);
			// }
		// }
		// s->setScale(s->getScale() + 1);
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