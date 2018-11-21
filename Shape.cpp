#include "shapegame"
shapegame::Shape::Shape(
        float height,
        float width,
        ShapeType type,
        Position pos,
        Color color) :
                        Object(pos),
                        _height(height),
                        _width(width),
                        _color(color),
                        type(type) {}

shapegame::Shape::Shape(float height, float width, ShapeType type, Color color) :
    Shape(height, width, type, Position(0.0, 0.0), color) {}

float shapegame::Shape::height() const {return this->_height;}
float shapegame::Shape::width() const {return this->_width;}

void shapegame::Shape::putAt(double x, double y){
    this->pos.setX(x);
    this->pos.setY(y);
    this->_dirty = true;
}
void shapegame::Shape::putAt(Position pos){
    this->putAt(pos.x(), pos.y());
}

void shapegame::Shape::move(double x, double y){
    this->pos.setX(this->pos.x() + x);
    this->pos.setY(this->pos.y() + y);
    this->_dirty = true;
}
void shapegame::Shape::move(Position pos){
    this->move(pos.x(), pos.y());
}
void shapegame::Shape::update() {
    std::cout << "shape update" << std::endl;
}
void shapegame::Shape::handleInput(GLFWwindow *w) {
}
void shapegame::Shape::onAdd() {
}