#define NUM_BODY_NODES 10
#define NODE_SIZE 10
#define MOVE_AMOUNT NODE_SIZE
#define SPEED_MS 75 
#define BODY_COLOR Color::KATIE_PINK


#include "shapegame"
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
    ~BodyNode(){
    }

    void onAdd() {
        this->setPosition(
            this->prev->pos.getX(),
            this->prev->pos.getY() + this->prev->getHeight()
        );
    }
    Position prevPos;
    void setPrev() {
        prevPos.setX(this->pos.getX());
        prevPos.setY(this->pos.getY());
    }
    void tick() {
        setPrev();
        this->setPosition(this->prev->prevPos);
    }
    void update() override {
    }
    void onKill() override {
        if (this->prev){
            this->prev->next = this->next;
        }
        if (this->next){
            this->next->prev = this->prev;
        }
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

    // void update() override {}
    void onAdd() override {
        auto myTimer = new shapegame::Timer(SPEED_MS, true, true, [this]() {
            this->tick();
        });
        Game::inst().scene->addChild(myTimer);
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

int main() {
    shapegame::Game game;
    glfwSetErrorCallback(error_callback);


    HeadNode *head = new HeadNode();
    BodyNode *body[NUM_BODY_NODES];

    // create the nodes
    for (int i = 0; i < NUM_BODY_NODES; i++) {
        body[i] = new BodyNode();
    }

    // set up node pointers
    for (int i = 0; i < NUM_BODY_NODES; i++) {
        if (i == 0) { //head node
            head->next = body[i];
            body[i]->prev = head;
            if (NUM_BODY_NODES > 1)
                body[i]->next = body[i + 1];
            continue;
        }
        if (i == (NUM_BODY_NODES -1)) { // tail node
            body[i]->prev = body[i - 1];
            continue;
        }
        body[i]->next = body[i + 1]; //next node
        body[i]->prev = body[i - 1]; //previous node
    }
    game.scene->addChild(head);
    for (int i = 0; i < NUM_BODY_NODES; i++) {
        game.scene->addChild(body[i]);
    }
    game.scene->addChildAs<Timer>(new Timer(100, true, true, [=](){
        head->color.set(
            head->color.r,
            head->color.g,
            head->color.b,
            head->color.a - 0.01
        );
    }));

    int i = -1;
    Timer *killTimer = new shapegame::Timer(1000, true, true, [=]() mutable {
        if (NUM_BODY_NODES + i > -1){
            BodyNode *node = body[NUM_BODY_NODES + i];
            node->kill();
            i--;
        }
    }, false);

    Game::inst().scene->addChild(killTimer);

    game.run();
}
