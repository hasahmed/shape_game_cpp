#include "shapegame"
using namespace shapegame;

int main() {
    shapegame::Game game;
    Rectangle *rect = new Rectangle(10, 10, Position(10, 10), Color::KATIE_PINK);
    Timer *t = new Timer(1000, false, false, [=]() {
        rect->kill();
    }, false);
    t->start();

    game.scene->addChild(*t);
    game.scene->addChild(*rect);
    game.run();
}
