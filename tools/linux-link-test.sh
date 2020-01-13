mkdir tmp
cp zip-dist/shapegame.zip tmp
cp resources/minmal-example.cpp tmp
cd tmp
unzip shapegame.zip
g++ -std=c++17 -o main main.cpp `pkg-config --cflags glfw3` -I./shapegame/deps -I./shapegame/include shapegame/platform/linux/shapegame.a `pkg-config
--libs glfw3`
