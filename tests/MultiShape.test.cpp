#include <assert.h>
#include <string>
#include <iostream>
#include "../shapegame"

using namespace shapegame;

class TwoRects : public MultiShape {
	public:
	TwoRects(Position pos): MultiShape(pos) {
		this->shapes.push_back((Shape*) new Rectangle(100, 100, pos, Color::BLACK));
		this->shapes.push_back((Shape*) new Rectangle(100, 100, Position(pos.getX() + 200, pos.getY()), Color::BLACK));
	}
};

int main(){
	// Object *controller = new Object(Position(0, 0));
	// auto r1 = new Rectangle(100, 100, controller->pos, Color::BLACK);
	// auto r2 = new Rectangle(100, 100, Position(controller->pos.getX() + 200, controller->pos.getY()), Color::BLACK);
	// std::vector<Object*> shapes {r1, r2};
	// MultiShape *m = new MultiShape(controller, shapes);
	// m->setPosition(10, 10);

	// m->setPosition(10, 10);

	Game g;
	// auto tr = new TwoRects(Position(100, 100));
	// g.scene->addChild(tr);
	// // auto r = new Rectangle(100, 100, Position(10, 10), Color::BLACK);
	// // g.scene->addChild(r);
	// g.scene->addChild(new Timer(0, true, true, [=]{
	// 	tr->setPosition(tr->pos.getX() + 1, tr->pos.getY());
	// }));


	g.run();
}

