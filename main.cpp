// #define NUM_NODES 2304
#define NUM_NODES 23
#define NODE_SIZE 10
#define MOVE_AMOUNT NODE_SIZE
#define SPEED_MS 75 
#define BODY_COLOR Color::KATIE_PINK


#include "shapegame"
#include <thread>
#include <chrono>
using namespace shapegame;


void error_callback(int error, const char* description) {
    puts(description);
}

// class HeadNode;
class BodyNode : public Rectangle {
    public:
    BodyNode *prev = nullptr;
    BodyNode *next = nullptr;
    BodyNode():
        Rectangle(NODE_SIZE, NODE_SIZE, Position(), BODY_COLOR) {}


    void onAdd() {
        this->setPosition(
            this->prev->pos.x(),
            this->prev->pos.y() + this->prev->height()
        );
    }
    Position prevPos;
    void setPrev() {
        prevPos.setX(this->pos.x());
        prevPos.setY(this->pos.y());
    }
    void tick() {
        setPrev();
        this->setPosition(this->prev->prevPos);
    }
    void update() {
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

    void tick() {
        this->setPrev();
        tickChildren(this->next);
        switch(this->moveDir) {
            case Dir::UP:
                this->translate(0, -MOVE_AMOUNT);
                break;
            case Dir::DOWN:
                this->translate(0, MOVE_AMOUNT);
                break;
            case Dir::LEFT:
                this->translate(-MOVE_AMOUNT, 0);
                break;
            case Dir::RIGHT:
                this->translate(MOVE_AMOUNT, 0);
                break;
        }
    }
    void tickChildren(BodyNode *b) {
        if (!b) return;
        b->tick();
        tickChildren(b->next);
    }

    void update() {}
    void onAdd() {
        auto myTimer = new shapegame::Timer(SPEED_MS, true, true, [this]() {
            this->tick();
        });
        Game::inst().scene->addChild(*myTimer);
    }

    void onKeyPress(int key, int action) override {
        if (action != GLFW_PRESS) return;
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(Game::inst().getWindow()->window_handle, true);
        if (key == GLFW_KEY_1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (key == GLFW_KEY_2)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (key == GLFW_KEY_UP) {
            this->moveDir = Dir::UP;
        }
        else if (key == GLFW_KEY_DOWN) {
            this->moveDir = Dir::DOWN;
        }
        else if (key == GLFW_KEY_LEFT) {
            this->moveDir = Dir::LEFT;
        }
        else if (key == GLFW_KEY_RIGHT) {
            this->moveDir = Dir::RIGHT;
        } 
    }

};
// HeadNode *head;
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     if (key == GLFW_KEY_ESCAPE)
//         glfwSetWindowShouldClose(window, true);
//     if (key == GLFW_KEY_1)
//         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//     if (key == GLFW_KEY_2)
//         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//     head->keyCallback(key);
// }

int main() {
    shapegame::Game game;
    HeadNode *head = new HeadNode();
    glfwSetErrorCallback(error_callback);

    game.scene->addChild(*head);

    BodyNode *body[NUM_NODES];

    for (int i = 0; i < NUM_NODES; i++) {
        body[i] = new BodyNode();
    }


    head->next = body[0];
    body[0]->prev = head;
    body[0]->next = body[1];


    for (int i = 1; i < NUM_NODES; i++) {
        body[i]->prev = body[i - 1];
        if (i < NUM_NODES - 1)
            body[i]->next = body[i + 1];
    }

    // body[0]->_color = Color::BLACK;
    // body[1]->_color = Color::BLUE;
    // body[2]->_color = Color::GREEN;
    // body[NUM_NODES -1]->_color = Color::PINK;

    for (int i = 0; i < NUM_NODES; i++) {
        game.scene->addChild(*body[i]);
    }
    game.run();
}
