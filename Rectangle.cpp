#include "shapegame"

shapegame::Rectangle::Rectangle(
        float height,
        float width,
        Position pos,
        Color color) : Shape(height, width, ShapeType::Rectangle, pos, color) {}

void shapegame::Rectangle::update(){
    std::cout << "rectangle update" << std::endl;
    this->move(0, 1.5);
}