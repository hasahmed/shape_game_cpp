#pragma once
#include "Scene.hpp"
namespace shapegame {
    class Color {
        private:
            float _color[4];
        public:
            Color(float red, float green, float blue, float alpha);
            Color(float red, float green, float blue);
            Color();
            float* getRawColor();
            void set(float red, float green, float blue);
            void set(float red, float green, float blue, float alpha);
            void set(Color& c);
            float r;
            float g;
            float b;
            float a;

            static Color BLACK;
            static Color WHITE;
            static Color LIGHT_GRAY;
            static Color GRAY;
						static Color DARK_GRAY;
            static Color RED;
            static Color PINK;
            static Color KATIE_PINK;
            static Color GREEN;
            static Color BLUE;
            static Color LIGHT_BLUE;
            static Color YELLOW;
            static Color PURPLE;
            static Color NIL;
            static Color ORANGE;
            static Color CYAN;
            static Color TEAL;
            static Color NAVY;
            static Color MAROON;
            static Color OLIVE;
            static Color LIME;
            static Color CORAL;
            static Color SALMON;
            static Color GOLD;
            static Color INDIGO;
            static Color VIOLET;
            static Color TURQUOISE;
            static Color MINT;
            static Color LAVENDER;
            static Color PEACH;
            static Color BROWN;
            static Color TAN;
            static Color CRIMSON;
    };
}

