#include "shapegame.hpp"
#include <vector>
using namespace shapegame;


class Box : public MultiShape {
	public:
	Box(Point pos): MultiShape(pos) {
		auto top = new Rectangle(100, 10, pos, Color::BLACK);
		auto left = new Rectangle(10, 100, pos, Color::BLACK);

		this->addShape(top);
		this->addShape(left);
	}
};
class Follower : public Component {
	Triangle *toFollow;
	public:
		Follower(Triangle *toFollow) {
			this->toFollow = toFollow;
		}
		void update(Entity *ent) override {
			ent->setPosition(this->toFollow->getCenter());
		}
};
class Mover: public Component {
	public:
		void update(Entity *ent) override {
			ent->setPosition(ent->pos.getX() + 0.1, ent->pos.getY() + 0.1);
		}
};
class Player : public TriangleIsosceles {
	float scaleStep = 0.5;
	public:
		Player(Point pos): TriangleIsosceles(100, 200, pos, Color::PEACH) {
			// this->addComponent(new Follower(this));
			// this->addComponent(new Mover);
		}
		void update() override {
			float maxScale = 1.2;
			float minScale = 0.2;
			this->scale += scaleStep * G::dt;
			if (this->scale.x >= maxScale) {
				scaleStep = -scaleStep;
			}
			if (this->scale.x <= minScale) {
				scaleStep = abs(scaleStep);
			}
			// std::cout << this->scale << std::endl;
			// G::fps
			// printf("Point{%f}{%f}\n", this->pos.getX(), this->pos.getY());
		}
};

int main() {

	Game g(1200, 700, "Multi Test");
	g.scene->setBackgroundColor(Color::DARK_GRAY);
	g.scene->addChild(std::make_unique<DebugKeyHandler>());
	g.scene->addChild(new Rectangle(100, 100, Point(20, 20), Color::LIGHT_BLUE));
	g.scene->addChild(new TriangleIsosceles(100, 200, Point(600, 300), Color::KATIE_PINK));
	Player *p = (Player*) g.scene->addChild(new Player(Point(300, 600)));
	p->scale = {0.1, 0.1};
	// float circleX = (p->pos.getX() + p->second.getX() + p->third.getX()) / 3;
	// float circleY = (p->pos.getY() + p->second.getY() + p->third.getY()) / 3;
	Circle *x = (Circle*) g.scene->addChild(new Circle(p->getCenter(), 30, Color::LAVENDER));
	x->addComponent(new Follower(p));
	// auto x = g.scene->addChild(std::make_unique<Box>(Point(100, 100)));
	// x->kill();
	g.run();
}