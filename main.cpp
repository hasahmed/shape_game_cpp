#define NUM_NODES 10
#define NODE_SIZE 10
#define MOVE_AMOUNT NODE_SIZE
#define SPEED_MS 100
#include "shapegame"
#include <thread>
#include <chrono>
using namespace shapegame;
void error_callback(int error, const char* description)
{
    puts(description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// class HeadNode;
class BodyNode : public Rectangle {
    public:
    BodyNode *prev = nullptr;
    BodyNode *next = nullptr;
    BodyNode():
        Rectangle(NODE_SIZE, NODE_SIZE, Position(), Color::BLACK) {}


    void onAdd() {
        this->putAt(
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
        this->putAt(this->prev->prevPos);
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
        this->handleKeys();
        tickChildren(this->next);
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
    void tickChildren(BodyNode *b) {
        if (!b) return;
        b->tick();
        tickChildren(b->next);
    }

    void handleKeys() {
        GLFWwindow *w = Game::inst().getWindow()->window_handle;
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
    }
    void onAdd() {

        // shapegame::Timer
        // myTimer = new shapegame::Timer(1000, this->_shapegame_timerCallback);
        // std::cout << "the head has been added" << std::endl;
        // Shape *myTimer = new BodyNode();
        // Game::inst().scene->addChild(*myTimer);
    }


    void _shapegame_timerCallback() {
        this->tick();
    }

};

bool run = true;

void timer(int milliseconds, HeadNode *head, BodyNode *body[NUM_NODES]) {
    while(run) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        head->tick();
    }
}

int main() {
    shapegame::Game game;
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(game.getWindow()->window_handle, key_callback);

    HeadNode *head = new HeadNode();
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

    for (int i = 0; i < NUM_NODES; i++)
        game.scene->addChild(*body[i]);

    std::thread t1(timer, SPEED_MS, head, body);

    game.run();
    // Game::inst().run();
    run = false;
    t1.join();
}
