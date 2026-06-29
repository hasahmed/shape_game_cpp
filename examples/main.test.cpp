#include "shapegame.hpp"
#include <vector>
using namespace shapegame;


class Box : public MultiShape {
	public:
	Box(Position pos): MultiShape(pos) {
		auto top = new Rectangle(100, 10, pos, Color::BLACK);
		auto left = new Rectangle(10, 100, pos, Color::BLACK);

		this->addShape(top);
		this->addShape(left);
	}
};
class Mover : public Component {
	public:
		void update(Entity *ent) override {
			ent->translate(Point(0, 1));
		}
};
class Player : public TriangleIsosceles {
	public:
		Player(Position pos): TriangleIsosceles(100, 200, pos, Color::PEACH) {
			this->addComponent(new Mover());
		}
		void update() override {
			// this->setPosition(this->pos.getX() + 10, this->pos.getY() + 10);
			this->translate(1, 0);
			printf("Position{%f}{%f}\n", this->pos.getX(), this->pos.getY());
		}
};

int main() {

	Game g(1200, 700, "Multi Test");
	g.scene->setBackgroundColor(Color::DARK_GRAY);
	g.scene->addChild(std::make_unique<DebugKeyHandler>());
	g.scene->addChild(new Rectangle(100, 100, Position(20, 20), Color::LIGHT_BLUE));
	g.scene->addChild(new TriangleIsosceles(100, 200, Position(600, 300), Color::KATIE_PINK));
	g.scene->addChild(new Player(Position(300, 600)));
	// auto x = g.scene->addChild(std::make_unique<Box>(Position(100, 100)));
	// x->kill();
	g.run();
}