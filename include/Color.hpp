#pragma once
namespace shapegame {
    class Color {
        private:
            float _color[4];
        public:
            Color(float r, float g, float b, float a);
            Color(float r, float g, float b);
    };
}

