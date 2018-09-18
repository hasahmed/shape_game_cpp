#include <stdexcept>
#include "shapegame"

#define EPSILON 0.001

shapegame::Triangle::Triangle(
        float height,
        float width,
        float angle1,
        float angle2,
        Position pos,
        Color color) :
   Shape(height, width, ShapeType::Triangle, pos, color),
    _angles{angle1, angle2, 360.0f - (angle1 + angle2)} {
        if (((_angles[0] + _angles[1] + _angles[2]) - 360.0f) < EPSILON)
            throw std::invalid_argument("Angles must add up to 360");
    }

//shapegame::Triangle::Triangle(
        //float height,
        //float width,
        //float angle1,
        //float angle2,
        //double x,
        //double y,
        //Color color) :
    //Triangle(height, width, angle1, angle2, Position(x, y), color) {}
