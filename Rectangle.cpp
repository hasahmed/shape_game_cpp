#include "shapegame"

shapegame::Rectangle::Rectangle(
        float height,
        float width,
        Position pos,
        Color color) : Shape(height, width, ShapeType::Rectangle, pos, color) {}

void shapegame::Rectangle::update(){
}