##### Table of Contents
[What Is It?](#wat)

[Quick Start?](#quickstart)


<a name="wat">
Shapegame
</a>
Shapegame is a 2D game engine for drawing shapes written in modern C++.

In this engine you cannot draw anything but shapes. No images, or text or anything. Just shapes.

## Why?
Why write a game engine? There are about a million game engines and they are all faster and better than this one.
I wrote this game engine as a learning experience for myself. I wanted to learn C++ and OpenGL.

## Should I Use This for My Game?
Probably not. This engine is a toy intended for drawing shapes easily in C++. If you want to make a real game I would
personally recommend Godot.


# Quickstart

```C++
#include "shapegame"
using namespace shapegame;
int main() {
	Game game(400, 400, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(new TriangleIsosceles(100, 100, pos, Color::BLACK));
}
```