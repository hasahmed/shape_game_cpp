#include <iostream>
#include "shapegame.hpp"

using namespace shapegame;

class Car : public Triangle {
	public:
		Car(): Triangle() {}
		void honk(){
			std::cout << "BEEP BEEP" << std::endl;
		}
};
int main() {
	Game game;
	auto car = game.scene->addChildAs<Car>(std::make_unique<Car>());
	car->honk();
	game.run();
}
