mkdir tmp
cp zip-dist/shapegame.zip tmp
cp resources/minmal-example.cpp tmp
cd tmp
unzip shapegame.zip
g++ -std=c++17 -o main main.cpp -I./shapegame/include shapegame/platform/mac/shapegame.a -lglfw -framework Cocoa -framework IOKit -framework CoreVideo
-framework OpenGL
