#include <memory>
namespace shapegame {
    class Game {
        private:
            std::unique_ptr<Window> _window;
            std::unique_ptr<GLHandler> _glHandler;
        public:
            Game();
    };
}
