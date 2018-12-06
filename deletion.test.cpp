#include "shapegame"
using namespace shapegame;
int main(){
	Game game;


	Rectangle *rectVect[100];

	for (int i = 0; i < 100; i++) {
		rectVect[i] = new Rectangle(5, 100, Position(i * 2, (i + 2) * 5), Color::BLUE);
		game.scene->addChild(*rectVect[i]);
	}


	Timer *t = new Timer(1000, false, true, [=](){
		for (int i = 0; i < 50; i++)
			rectVect[i * 2]->kill();
		std::cout << "hello" << std::endl;
	}, false);

	game.scene->addChild(*t);

	game.run();
}