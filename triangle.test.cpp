#include "shapegame"
using namespace shapegame;
class KeyHandler : public Object {
    void onKeyPress(int key, int action) override {
        if (action != GLFW_PRESS) return;
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(Game::inst().getWindow()->window_handle, true);
        if (key == GLFW_KEY_1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (key == GLFW_KEY_2)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
};

int main() {
    shapegame::Game game(720, 720, "Triangle Test");
    game.scene->addChild(new KeyHandler());
    game.scene->addChild(new Triangle(Position(10, 10), Point(5, 0), Point(20, 100), Color::WHITE));
    // game.scene->setBackgroundColor(Color::BLACK);
    game.scene->addChild(new Triangle(Position(10, 10), Point(60, 100), Point(100, 10), Color::YELLOW));
    game.scene->addChild(
        new Triangle(Position(110, 10), Point(110, 600), Point(1120, 10), Color::GREEN)
        );
    auto *t = game.scene->addChildAs<Triangle>(
        new Triangle(Position(10, 0), Point(600, 650), Point(9, 700), Color::PURPLE));
    auto *timer = game.scene->addChildAs<Timer>(new Timer(0, true, true, [=](){
        using namespace std;
        cout << t->third.getX() << endl;
        t->translate(0.1, 0);
        t->setThird(Point(t->third.getX() - 1, t->third.getY()));
        cout << t->third.getX() << endl;
    }));
    t->translate(50, 0);
    timer->start();
    game.run();
}
