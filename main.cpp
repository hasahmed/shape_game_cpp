#define NUM_NODES 100
#define NODE_SIZE 9
#define MOVE_AMOUNT NODE_SIZE + 1
#define SPEED_MS 50
#include "shapegame"
#include <thread>
#include <chrono>
using namespace shapegame;
void error_callback(int error, const char* description)
{
    puts(description);
}
void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // std::cout << key << std::endl;
}

// class HeadNode;
class BodyNode : public Rectangle {
    public:
    BodyNode *prev = nullptr;
    BodyNode():
        Rectangle(NODE_SIZE, NODE_SIZE, Position(), Color::BLACK) {}


    void onAdd() {
        this->putAt(
            this->prev->pos.x(),
            this->prev->pos.y() + this->prev->height() + 1
        );
    }
    Position prevPos;
    void setPrev() {
        prevPos.setX(this->pos.x());
        prevPos.setY(this->pos.y());
    }
    void tick() {
        setPrev();
        this->putAt(this->prev->prevPos);
        // this->move(0, );
        // std::cout << this->prev->pos.y() << std::endl;
    }
    void update() {
        // tick();
        // setPrev();
        // this->putAt(this->prev->prevPos);
        // this->move(0, 2);
        // std::cout << this->prev->pos.y() << std::endl;
    }
};

class HeadNode: public BodyNode {
    public:

    HeadNode(): BodyNode() {
        this->pos.setX(240);
        this->pos.setY(240);
    }

    enum Dir {
        LEFT, RIGHT, UP, DOWN
    };

    Dir moveDir = Dir::UP;

    void tick(GLFWwindow *w) {
        this->setPrev();
        this->handleKeys(w);
        switch(this->moveDir) {
            case Dir::UP:
                this->move(0, -MOVE_AMOUNT);
                break;
            case Dir::DOWN:
                this->move(0, MOVE_AMOUNT);
                break;
            case Dir::LEFT:
                this->move(-MOVE_AMOUNT, 0);
                break;
            case Dir::RIGHT:
                this->move(MOVE_AMOUNT, 0);
                break;
        }
    }

    void handleKeys(GLFWwindow *w) {
        if (glfwGetKey(w, GLFW_KEY_UP)) {
            this->moveDir = Dir::UP;
        }
        else if (glfwGetKey(w, GLFW_KEY_DOWN)) {
            this->moveDir = Dir::DOWN;
        }
        else if (glfwGetKey(w, GLFW_KEY_LEFT)) {
            this->moveDir = Dir::LEFT;
        }
        else if (glfwGetKey(w, GLFW_KEY_RIGHT)) {
            this->moveDir = Dir::RIGHT;
        }
    }
    void update() {
        // this->setPrev();
        // this->move(0, -MOVE_AMOUNT);
        // this->putAt(this->pos.x(), this->pos.y() - MOVE_AMOUNT);
    }
    void onAdd() {
        std::cout << "the head has been added" << std::endl;
    }

};

bool run = true;

void timer(int milliseconds, HeadNode *head, BodyNode *body[NUM_NODES], GLFWwindow *w) {
    while(run) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        head->tick(w);
        for (int i = 0; i < NUM_NODES; i++) {
            body[i]->tick();
        }
    }
}

int main() {
    shapegame::Game game;
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(game.getWindow()->window_handle, _key_callback);

    HeadNode *head = new HeadNode();
    game.scene->addChild(*head);

    BodyNode *body[NUM_NODES];

    for (int i = 0; i < NUM_NODES; i++) {
        body[i] = new BodyNode();
        if (i == 0)
            body[i]->prev = head;
        else
            body[i]->prev = body[i -1];
    }

    for (int i = 0; i < NUM_NODES; i++) {
        game.scene->addChild(*body[i]);
    }

    std::thread t1(timer, SPEED_MS, head, body, game.getWindow()->window_handle);

    // for (BodyNode *bn : snake->body) {
    //     game.scene->addChild(*bn);
    // }
    // Player *const tmp = new Player(240, 240, Position(0, 0), Color::YELLOW);
    // Player &tmp2 = *tmp;
    // Rectangle *const tmp = new Rectangle(240, 240, Position(0, 0), Color::YELLOW);
    // Rectangle &tmp2 = *tmp;

    // game.scene->addChild(tmp2);
    game.run();
    run = false;
    t1.join();
}
