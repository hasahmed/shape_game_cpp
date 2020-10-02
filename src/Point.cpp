#include "shapegame.hpp"
using namespace shapegame;
Point::Point(float x, float y) : x(x), y(y) {}
Point::Point(): Point(0, 0) {}
Point::~Point() {}
float Point::getX() const {return this->x;}
float Point::getY() const {return this->y;}
void Point::setX(const float x){
	this->x = x;
}
void Point::setY(const float y){
	this->y = y;
}
bool Point::operator==(const Point& rhs) {
	return this->x == rhs.x && this->y == rhs.y;
}
Point Point::operator+(const Point& rhs) {
	return Point(this->x + rhs.x, this->y + rhs.y);
}
Point Point::operator+(const float& rhs) {
	return Point(this->x + rhs, this->y + rhs);
}
Point Point::operator-(const Point& rhs) {
	return Point(this->x - rhs.x, this->y - rhs.y);
}
Point Point::operator-(const float& rhs) {
	return Point(this->x - rhs, this->y - rhs);
}
Point Point::operator*(const Point& rhs) {
	return Point(this->x * rhs.x, this->y * rhs.y);
}
Point Point::operator*(const float& rhs) {
	return Point(this->x * rhs, this->y * rhs);
}
void Point::operator+=(const Point& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
}
void Point::operator+=(const float& rhs) {
	this->x += rhs;
	this->y += rhs;
}
void Point::operator-=(const Point& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
}
void Point::operator-=(const float& rhs) {
	this->x -= rhs;
	this->y -= rhs;
}
void Point::operator*=(const Point& rhs) {
	this->x *= rhs.x;
	this->y *= rhs.y;
}
void Point::operator*=(const float& rhs) {
	this->x *= rhs;
	this->y *= rhs;
}

Point::operator bool() const {
	return this->x or this->y;
}
std::ostream& operator<< (std::ostream& stream, const shapegame::Point& rObj) {
	using namespace std;
	cout << "[" << rObj.x << "," << rObj.y << "]";
	return stream;
}