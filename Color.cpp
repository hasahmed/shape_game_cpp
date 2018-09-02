#include "shapegame"

shapegame::Color::Color(float r, float g, float b, float a) {
    _color[0] = r;
    _color[1] = g;
    _color[2] = b;
    _color[3] = a;
}

shapegame::Color::Color(float r, float g, float b) : Color(r, g, b, 1.0) {}
