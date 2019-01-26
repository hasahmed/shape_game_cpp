/**
 * SHMUP
 * 
 * 
 * 
 */
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
	Game game;
	game.scene->addChild(new KeyHandler());
	game.run();
}