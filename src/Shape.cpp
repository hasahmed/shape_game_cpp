#include "shapegame.hpp"
using namespace shapegame;
Shape::~Shape(){
	#if PRINT_DESTRUCTION
	std::cout << "Shape Killed" << std::endl;
	#endif
}
Shape::Shape(
        float height,
        float width,
        ShapeType type,
        Position pos,
        Color color
        ) :
            Entity(pos),
            color(color),
            type(type) {
							this->name = "Shape";
							this->setPosition(pos);
							this->width = width;
							this-> height = height;
						}

Shape::Shape(float height, float width, ShapeType type, Color color) :
    Shape(height, width, type, Position(0.0, 0.0), color) {}
// float Shape::getHeight() const {return this->_height;}
// float Shape::getWidth() const {return this->_width;}


bool Shape::isColliding(Shape &other) {
    if (this->pos.getX() + this->getWidth() > other.pos.getX() && // right with left
        other.pos.getX() + other.getWidth() > this->pos.getX() &&
        this->pos.getY() + this->getHeight() > other.pos.getY() &&
        other.pos.getY() + other.getHeight() > this->pos.getY()
    ) {
        return true;
    }
    return false;
}

void Shape::onCollisionStart(Shape &other) {}
void Shape::onCollisionStop(Shape &other) {}
void Shape::onColliding(Shape &other) {}

void Shape::translate(float x, float y) {
	this->setPosition(this->pos.getX() + x, this->pos.getY() + y);
}
void Shape::translate(Position pos){
    this->translate(pos.getX(), pos.getY());
}
// std::ostream& operator<< (std::ostream& stream, const Shape& shape) {
// 	using namespace std;
// 	cout << "Address: " << &shape << endl;
// 	cout << "X: " << shape.pos.getX() << endl;
// 	cout << "Y: " << shape.pos.getY() << endl;
// 	cout << "Type: " << (int)shape.type << endl;
// 	cout << "Height: " << shape.getHeight() << endl;
// 	cout << "Width: " << shape.getWidth() << endl;
// 	return stream;
// }