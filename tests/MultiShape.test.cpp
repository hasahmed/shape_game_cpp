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
	// new Position(100, 100);
	TwoRects *t = new TwoRects(Position(100, 100));
	// MultiShape m(Position(100, 100));
	delete t;
}