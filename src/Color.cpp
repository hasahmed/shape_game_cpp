#include "shapegame.hpp"

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

Color  Color::BLACK       =  Color(0.0,   0.0,   0.0);
Color  Color::WHITE       =  Color(1.0,   1.0,   1.0);
Color  Color::LIGHT_GRAY  =  Color(0.8,   0.8,   0.8);
Color  Color::GRAY        =  Color(0.5,   0.5,   0.5);
Color  Color::DARK_GRAY   =  Color(0.3,   0.3,   0.3);
Color  Color::RED         =  Color(1.0,   0.0,   0.0);
Color  Color::GREEN       =  Color(0.0,   1.0,   0.0);
Color  Color::BLUE        =  Color(0.0,   0.0,   1.0);
Color  Color::LIGHT_BLUE  =  Color(0.5,   0.7,   1.0);
Color  Color::YELLOW      =  Color(1.0,   1.0,   0.0);
Color  Color::PURPLE      =  Color(1.0,   0.0,   1.0);
Color  Color::KATIE_PINK  =  Color(1,     .41,   .70);
Color  Color::PINK        =  Color(1,     0.5,   0.9);
Color  Color::ORANGE      =  Color(1.0,   0.5,   0.0);
Color  Color::CYAN        =  Color(0.0,   1.0,   1.0);
Color  Color::TEAL        =  Color(0.0,   0.5,   0.5);
Color  Color::NAVY        =  Color(0.0,   0.0,   0.5);
Color  Color::MAROON      =  Color(0.5,   0.0,   0.0);
Color  Color::OLIVE       =  Color(0.5,   0.5,   0.0);
Color  Color::LIME        =  Color(0.75,  1.0,   0.0);
Color  Color::CORAL       =  Color(1.0,   0.5,   0.31);
Color  Color::SALMON      =  Color(0.98,  0.5,   0.45);
Color  Color::GOLD        =  Color(1.0,   0.84,  0.0);
Color  Color::INDIGO      =  Color(0.29,  0.0,   0.51);
Color  Color::VIOLET      =  Color(0.93,  0.51,  0.93);
Color  Color::TURQUOISE   =  Color(0.25,  0.88,  0.82);
Color  Color::MINT        =  Color(0.6,   1.0,   0.6);
Color  Color::LAVENDER    =  Color(0.71,  0.49,  0.86);
Color  Color::PEACH       =  Color(1.0,   0.85,  0.73);
Color  Color::BROWN       =  Color(0.59,  0.29,  0.0);
Color  Color::NIL         =  Color(0,   0,   0,    0);