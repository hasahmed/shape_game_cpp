#include "shapegame"

using namespace shapegame;

// all values should be between 0-1
Color::Color(float red, float green, float blue, float alpha) {
    this->set(red, green, blue, alpha);
}
Color::Color(float red, float green, float blue) : Color(red, green, blue, 1.0) {}

Color::Color(): Color(1, 1, 1) {}

float* Color::getRawColor(){
    return this->_color;
}
void Color::set(float red, float green, float blue, float alpha){
    this->_color[0] = red;
    this->_color[1] = green;
    this->_color[2] = blue;
    this->_color[3] = alpha;

    this->r = this->_color[0];
    this->g = this->_color[1];
    this->b = this->_color[2];
    this->a = this->_color[3];
}
void Color::set(float red, float green, float blue){
    this->set(red, green, blue, 1);
}
void Color::set(Color& c){
    float *rawColor = c.getRawColor();
    for(int i = 0; i < 4; i++)
        this->_color[i] = rawColor[i];
}

Color Color::BLACK = Color(0.0, 0.0, 0.0);
Color Color::WHITE = Color(1.0, 1.0, 1.0);
Color Color::RED = Color(1.0, 0.0, 0.0);
Color Color::GREEN = Color(0.0, 1.0, 0.0);
Color Color::BLUE = Color(0.0, 0.0, 1.0);
Color Color::YELLOW = Color(1.0, 1.0, 0.0);
Color Color::PURPLE = Color(1.0, 0.0, 1.0);
Color Color::PINK = Color(1, 0.5, 0.9);
Color Color::KATIE_PINK = Color(1, 0.41, 0.70);
