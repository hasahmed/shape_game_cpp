//#define NUM_BODY_NODES 100
//#define NODE_SIZE 10
//#define MOVE_AMOUNT NODE_SIZE
//#define SPEED_MS 75
//#define BODY_COLOR Color::KATIE_PINK
//
//
//#include <queue>
//#include "shapegame.hpp"
//using namespace shapegame;
//using namespace shapegame::Input;
//
//
//void error_callback(int error, const char* description) {
//    puts(description);
//}
//
//class BodyNode : public Circle {
//// class BodyNode : public Rectangle {
//    public:
//    BodyNode *prev = nullptr;
//    BodyNode *next = nullptr;
//    BodyNode():
//        // Rectangle(NODE_SIZE, NODE_SIZE, Position(), BODY_COLOR) {
//        Circle(Position(0, 0), NODE_SIZE, 10, BODY_COLOR) {
//        }
//    ~BodyNode(){
//    }
//
//    void onAdd() override {
//        this->setPosition(
//            this->prev->pos.getX(),
//            this->prev->pos.getY() + this->prev->getHeight()
//        );
//    }
//    Position prevPos;
//    void setPrev() {
//        prevPos.setX(this->pos.getX());
//        prevPos.setY(this->pos.getY());
//    }
//    void tick() {
//        setPrev();
//        this->setPosition(this->prev->prevPos);
//				this->scaleX(1.5);
//    }
//    void update() override {
//    }
//    void onKill() override {
//        if (this->prev){
//            this->prev->next = this->next;
//        }
//        if (this->next){
//            this->next->prev = this->prev;
//        }
//    }
//};
//
//class HeadNode: public BodyNode {
//    public:
//    bool colliding = false;
//    enum Dir {
//        LEFT, RIGHT, UP, DOWN
//    };
//    Dir moveDir = Dir::UP;
//    std::queue<Dir> moves;
//
//    HeadNode(): BodyNode() {
//        this->setPosition(240, 240);
//        // this->pos.setX(240);
//        // this->pos.setY(240);
//    }
//
//    // void onCollisionStop(Shape &other) override {
//    //     this->colliding = false;
//    //     puts("Colliding stopped");
//    // }
//
//    // void onCollisionStart(Shape &other) override {
//    //     puts("Colliding");
//    //     this->colliding = false;
//    //     // puts("Head Collision");
//    // }
//    // void onColliding(Shape &other) override {
//    // }
//
//    void tick() {
//        if (this->colliding)
//            return;
//        this->setPrev();
//        tickChildren(this->next);
//        Dir nextMove = this->moveDir;
//        if (!this->moves.empty()){
//            nextMove = this->moves.front();
//            this->moves.pop();
//        }
//        switch(nextMove) {
//            case Dir::UP:
//                this->translate(0, -MOVE_AMOUNT);
//                break;
//            case Dir::DOWN:
//                this->translate(0, MOVE_AMOUNT);
//                break;
//            case Dir::LEFT:
//                this->translate(-MOVE_AMOUNT, 0);
//                break;
//            case Dir::RIGHT:
//                this->translate(MOVE_AMOUNT, 0);
//                break;
//        }
//    }
//    void tickChildren(BodyNode *b) {
//        if (!b) return;
//        b->tick();
//        tickChildren(b->next);
//    }
//
//    // void update() override {}
//    void onAdd() override {
//        auto myTimer = new shapegame::Timer(SPEED_MS, true, true, [this]() {
//            this->tick();
//        });
//        Game::inst().scene->addChild(myTimer);
//    }
//
//    void onKeyPress(Input::Kb::Key key, Input::Action action) override {
//        if (action != Input::Action::DOWN) return;
//        if (key == Kb::Key::ESCAPE)
//            glfwSetWindowShouldClose(Game::inst().getWindow()->getWindowHandle(), true);
//        if (key == Kb::Key::N1)
//            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        if (key == Kb::Key::N2)
//            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//        if (key == Kb::Key::UP) {
//            this->moveDir = Dir::UP;
//            this->moves.push(Dir::UP);
//        }
//        else if (key == Kb::Key::DOWN) {
//            this->moveDir = Dir::DOWN;
//            this->moves.push(Dir::DOWN);
//        }
//        else if (key == Kb::Key::LEFT) {
//            this->moveDir = Dir::LEFT;
//            this->moves.push(Dir::LEFT);
//        }
//        else if (key == Kb::Key::RIGHT) {
//            this->moveDir = Dir::RIGHT;
//            this->moves.push(Dir::RIGHT);
//        } 
//    }
//
//};
//
//class Food : public Rectangle {
//    public: 
//        Food(): Rectangle(NODE_SIZE, NODE_SIZE, Position(210, 240), Color::YELLOW) {
//            // this->collidable = true;
//        }
//        // void onCollisionStart(Shape& other) override {
//        //     try {
//        //         HeadNode *h = dynamic_cast<HeadNode*>(&other);
//        //         this->kill();
//        //     } catch (std::bad_cast exp) {
//        //         puts("Not colliding with head");
//        //     }
//        //     puts("Food collided");
//        // }
//        // void onCollisionStop(Shape& other) override {
//        //     puts("Food stopped colliding");
//        // }
//        // void onColliding(Shape &other) override {
//        // }
//};
//
//int main() {
//    shapegame::Game game(720, 720, "Snake");
//    glfwSetErrorCallback(error_callback);
//
//
//    HeadNode *head = new HeadNode();
//    BodyNode *body[NUM_BODY_NODES];
//
//    // create the nodes
//    for (int i = 0; i < NUM_BODY_NODES; i++) {
//        body[i] = new BodyNode();
//    }
//
//    // set up node pointers
//    for (int i = 0; i < NUM_BODY_NODES; i++) {
//        if (i == 0) { //head node
//            head->next = body[i];
//            body[i]->prev = head;
//            if (NUM_BODY_NODES > 1)
//                body[i]->next = body[i + 1];
//            continue;
//        }
//        if (i == (NUM_BODY_NODES -1)) { // tail node
//            body[i]->prev = body[i - 1];
//            continue;
//        }
//        body[i]->next = body[i + 1]; //next node
//        body[i]->prev = body[i - 1]; //previous node
//    }
//    game.scene->addChild(head);
//    for (int i = 0; i < NUM_BODY_NODES; i++) {
//        game.scene->addChild(body[i]);
//    }
//    Game::inst().scene->setBackgroundColor(Color::GRAY);
//
//    game.run();
//}
