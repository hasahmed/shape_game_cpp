#pragma once
#include "Shape.hpp"
#include "shapegl.hpp"
namespace shapegame {
    class Rectangle : public Shape {
        public:
            Rectangle(float height, float width, Position pos, Color color);
            Rectangle();
            void update() override;
            void onAdd() override;
            void onKeyPress(int key, int action) override;
            ~Rectangle(){
                // std::cout << "deleted: Rectangle" << std::endl;
            }
    };
}
