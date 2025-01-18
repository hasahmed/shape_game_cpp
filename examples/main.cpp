#include <iostream>
//#include <unordered_set>
//#include <cstdlib>
//
//#include "shapegame.hpp"
//using namespace shapegame;
//
//
//// unused variable for giving the player a shadow
//const Color SHADOW_COLOR = Color(0, 0, 0, 0.5);
//
//
//const int ENEMY_WIDTH = 40;
//const int ENEMY_HEIGHT = 40;
//
//const int BULLET_WIDTH = 5;
//const int BULLET_HEIGHT = 30;
//
//const int SCREEN_WIDTH = 400;
//const int SCREEN_HEIGHT = 600;
//
//
//const int KILL_DOWN = 700; // the point at wich things should kill themselves below the screen
//const int KILL_UP = -30; // the point at wich things should kill themselves above the screen
//
//const int ENEMY_SPEED = 100;
//
//const int BULLET_SPEED = 30;
//
//const int PLAYER_WIDTH = 50;
//const int PLAYER_HEIGHT = 50;
//
//const int PLAYER_SHADOW_OFFSET_Y = 5;
//const int PLAYER_SHADOW_OFFSET_X = 10;
//
//
//const int BOTTOM_MARGIN = 10;
//
////enemy spawn frequency in millisecionds
//const int ENEMY_SPAWN_FREQUENCY_MS = 1000;
//
///* Forward declaration so that enemyList can contain Enemies, and
// * Enemy class can reference global enemyList */
//class Enemy;
//// enemy list for collision handling (not handled by engine)
//std::unordered_set<Enemy*> enemyList;
//
//
//// enemy class extends rectangle class
//class Enemy : public Rectangle {
//	// Public Enemy
//public:
//	// enemy constructor initilizes rectangle base class
//	Enemy(Position pos) : Rectangle(ENEMY_WIDTH, ENEMY_HEIGHT, pos, Color::RED) {
//		// adds its self to the enemy list for ad-hock (not handled by engine)
//		// collision handling
//		enemyList.insert(this);
//	}
//	// override update callback. Called every frame
//	void update() override {
//		// move the enemy down (ENEMY_SPEED * delta) (frame rate independant movement)
//		// on the y axsis every frame
//		this->translate(0, ENEMY_SPEED * Globals::dt);
//		/* If this enemy is below the screen */
//		if (this->pos.y > KILL_DOWN) {
//			/* kill its self */
//			this->kill();
//			// and remove from enemy list
//			enemyList.erase(this);
//		}
//	}
//};
//
//
//// Bullet class extends shapegame::Rectangle
//class Bullet : public Rectangle {
//public:
//	/* A constructor for our bullet class that takes a Position as an argument
//	 * It then initilizes the rectangle that will be representing the bullet
//	 * with a width, height, position, and color */
//	Bullet(Position pos) : Rectangle(BULLET_WIDTH, BULLET_HEIGHT, pos, Color::WHITE) {}
//
//
//	/* Override the update method. This will be called every frame by the
//	 * engine once the object instance is added to the scene */
//	void update() override {
//		/* Every frame move up pixels */
//		this->translate(0, -BULLET_SPEED);
//
//		/* If this bullet is above the screen */
//		if (this->pos.y < -KILL_UP) {
//			/* This kill its self */
//			this->kill();
//		}
//		// loop through every enemy in the enemyList
//		// to check to see if this bullet is colliding
//		for (Enemy* enemy : enemyList) {
//			if ( // if is collision with enemy
//					// this is collision checking code.
//					// Deciphering it is left as an exercise to the reader
//				this->pos.y < enemy->pos.y + ENEMY_HEIGHT &&
//				this->pos.y + BULLET_HEIGHT > enemy->pos.y &&
//				this->pos.x + BULLET_WIDTH > enemy->pos.x &&
//				this->pos.x < enemy->pos.x + ENEMY_WIDTH
//				) {
//				// if enemy and bullet are colliding,
//				// kill this (bullet)
//				this->kill();
//				// remove colliding enemy from enemyList
//				enemyList.erase(enemy);
//				// kill that enemy
//				enemy->kill();
//				// leave the for-loop (no need to do any more processesing)
//				break;
//			}
//		}
//	}
//};
//
///* Create a player class which extends
// * TriangleIsosceles built in class. In order to hook into the callbacks
// * of the engine you need to create a class that overrides the callback
// * methods
// */
//class Player : public MultiShape {
//public:
//	/* Construct the player with a triangle 100px wide, 100px tall
//	 * at position 100, 100, and with a color of green
//	 */
//	Player() : MultiShape() { // creates a multishape with a default position of 0,0
//		// add a shadow to the player. Note that the positions of the shapes
//		// being added to the multishape are NOT RELATIVE. They are all
//		// absolute positions. Also notice how we are adding the shadow
//		// FIRST. Before the player. This is because the z order of
//		// objects is defined by the order in which they were added
//		// i.e. objects added more recently will be added on top of 
//		// objects added before them
//		this->addShape(std::make_unique<TriangleIsosceles>(PLAYER_WIDTH, PLAYER_HEIGHT, Position(-PLAYER_SHADOW_OFFSET_X, PLAYER_SHADOW_OFFSET_Y), SHADOW_COLOR));
//		// this adds the player shape. Note that Position() by default
//		// has the x and y values set to 0s when no arguments are provided
//		this->addShape(std::make_unique<TriangleIsosceles>(PLAYER_WIDTH, PLAYER_HEIGHT, Position(), Color::GREEN));
//	}
//
//	/* Override the update method. This method is called every frame */
//	void update() override {
//		/* Set the X position of the player to the X position of the mouse */
//		this->setPosition(Position(Input::Mouse::getPos().x, SCREEN_HEIGHT - BOTTOM_MARGIN));
//		/* Move the player over half the players width in pixels so the mouse is in the middle */
//		/* Origin is the corner by default */
//		this->translate(-PLAYER_WIDTH / 2, 0);
//		//TriangleIsosceles 
//		//TriangleIsosceles(PLAYER_WIDTH, PLAYER_HEIGHT, Position(100, 100), Color::GREEN) {}
//	}
//	/* override the mouse click handler to recieve callbacks when
//	 * mouse clicks happen
//	 */
//	void onMouseClick(Input::Mouse::Btn btn, Input::Action action) override {
//		/* check to see if the left mouse button is down */
//		if (btn == Input::Mouse::Btn::LEFT && action == Input::Action::DOWN) {
//			/* if it is down then shoot */
//
//			/* A lot of things are happening here. Were creating an instance of
//			 * bullet using make_unique
//			 * Were adding that bullet to the scene.
//			 * Notice that we are getting the scene by accessing the game
//			 * instance via the inst() static method of the Game object.
//			 * Then notice that scene->addChild returns a reference to the
//			 * child that was added. We can use this reference to perform
//			 * operations on the object even though it is already added to the
//			 * scene. This is why we can move it around via the translate
//			 * method call below*/
//			Object* bullet = Game::inst().scene->addChild(std::make_unique<Bullet>(this->pos));
//			/* Move the bullet so it looks like its coming out of the tip of
//			 * the player */
//			bullet->translate(25, -40);
//		}
//	}
//};
//
//int main() {
//	std::cout << "Hello" << std::endl;
//	system("pause");
//}
#include "shapegame.hpp"
using namespace shapegame;
int main() {
	Game game(400, 400, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(new TriangleIsosceles(100, 100, Position(100, 100), Color::BLACK));

	game.run();
}
//	/* Create a new Game object with window width, height, and title */
//	Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "SHMUP");
//	// Set the background color of the scene
//	game.scene->setBackgroundColor(Color::BLUE);
//
//	//[> Add a convenience key handler that closes the window when escape is pressed <]
//	game.scene->addChild(std::make_unique<DebugKeyHandler>());
//
//	// Add a new player to the scene
//	game.scene->addChild(std::make_unique<Player>());
//	// Add a timer to the scene
//	game.scene->addChild(std::make_unique<Timer>(ENEMY_SPAWN_FREQUENCY_MS, true, true, []() {
//		// Add a new enemy every time the timer times out
//		int enemySpawnX = (rand() % (SCREEN_WIDTH - ENEMY_WIDTH));
//		Game::inst().scene->addChild(std::make_unique<Enemy>(Position(enemySpawnX, -(ENEMY_HEIGHT + 20))));
//		}
//	));
//	// finally starting the game
//	//game.run();
//	std::cout << shapegame::FileUtil::read("default.frag") << std::endl;
//	// exercise for the reader: give all object shadows (HINT: Make them MultiShapes)
//	// and also make all movement 'frame rate independent'
//}