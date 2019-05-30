#include "shapegame.hpp"
#include <vector>
using namespace shapegame;

// template <class T>
// class Spawner: public Object {
// 	private:
// 	Timer *t;
// 	public:
// 	Spawner(Position pos, unsigned int intervalMs): Object(pos) {
// 		this->t = Game::inst().scene->addChildAs<Timer>(new Timer(intervalMs, true, true, [=]() mutable {
// 			i++;
// 			std::cout << "Car spawned: " << i << std::endl;
// 			Game::inst().scene->addChild(new T(pos));
// 		}));
// 	}
// 	void onMouseClick(Mouse::Btn btn, Input::Action action) override {
// 		this->t->stop();
// 		this->kill();
// 	}
// };

class Box : public MultiShape {
	public:
	Box(Position pos): MultiShape(pos) {
		auto top = new Rectangle(100, 10, pos, Color::BLACK);
		auto left = new Rectangle(10, 100, pos, Color::BLACK);

		this->addShape(top);
		this->addShape(left);
	}
};

int main() {

	Game g(1200, 700, "Multi Test");
	g.scene->addChildAs<DebugKeyHandler>(new DebugKeyHandler());
		// g.scene->addChild(new Rectangle(10, 100, Position(100, 100), Color::BLACK));
	// auto x = g.scene->addChildAs<Box>(new Box(Position(100, 100)));
	auto x = g.scene->addChild(std::make_unique<Box>(Position(100, 100)));
	x->kill();
	g.run();
}