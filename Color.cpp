#include "shapegame"


// all values should be between 0-1
shapegame::Color::Color(float r, float g, float b, float a) {
    _color[0] = r;
    _color[1] = g;
    _color[2] = b;
    _color[3] = a;
}
shapegame::Color::Color(float r, float g, float b) : Color(r, g, b, 1.0) {}

shapegame::Color shapegame::Color::BLACK = Color(0.0, 0.0, 0.0);
shapegame::Color shapegame::Color::WHITE = Color(1.0, 1.0, 1.0);
shapegame::Color shapegame::Color::RED = Color(1.0, 0.0, 0.0);
shapegame::Color shapegame::Color::GREEN = Color(0.0, 1.0, 0.0);
shapegame::Color shapegame::Color::BLUE = Color(0.0, 0.0, 1.0);
shapegame::Color shapegame::Color::YELLOW = Color(1.0, 1.0, 0.0);
shapegame::Color shapegame::Color::PURPLE = Color(1.0, 0.0, 1.0);
