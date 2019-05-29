# Shapegame
A simple 2D Game Engine for Drawing Shapes In C++

## Table of Contents
* [What Is It?](#wat)
* [FAQ](#faq)
  * [Why Should I Use This?](#shouldi)
  * [Why Did You Make This?](#why)
* [Quick Start](#quickstart)


<a name="wat"></a>
### What Is It?
Shapegame is a 2D game engine for drawing shapes written in modern C++.
In this engine you cannot draw anything but shapes. No images, or text or anything. Just shapes.

## FAQ
<a name="faq" />


<a name="shouldi"></a>

### Why Should I Use This?
You probably shouldn't. This engine is a toy intended for drawing shapes easily in C++. If you want to make a real game I would
personally recommend [Godot](https://godotengine.org/). If you just want to draw some shapes using C++ and aren't
worried about performance, or shipping a game then this might be for you.


<a name="why"></a>

### Why Did You Make This?
Why write a game engine? There are about [a million game engines](https://en.wikipedia.org/wiki/List_of_game_engines)
and they are all probably better and faster than this one.
I wrote this game engine as a learning experience for myself. I wanted to learn C++ and OpenGL. To that end I consider
it a success.



## Quickstart

```C++
#include "shapegame"
using namespace shapegame;
int main() {
	Game game(400, 400, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(new TriangleIsosceles(100, 100, pos, Color::BLACK));
}
```