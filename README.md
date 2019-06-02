# Shapegame
A simple 2D Game Engine for Drawing Shapes In C++

<a name="motivation"></a>
# Motivation
Want to quickly draw some shapes without learning an entire game engine? This aims to be that. Minimal shape drawing in C++.


## Table of Contents
* [Motivation](#motivation)
* [Quick Start](#quickstart)
* [Docs](#docs)
  * [Overview](#overview)
  * [Classes](#classes)
	  * [Shape](#shape)
	  * [Scene](#scene)
	  * [Position](#position)
* [FAQ](#faq)
	* [What Is It?](#wat)
  * [Who Is This For?](#who)
  * [Why Should I Use This?](#shouldi)
  * [Why Did You Make This?](#why)


## Quickstart

```C++
#include "shapegame.hpp"
using namespace shapegame;
int main() {
	Game game(400, 400, "My New Game");
	game.scene->setBackgroundColor(Color::BLUE);
	game.scene->addChild(new TriangleIsosceles(100, 100, pos, Color::BLACK));
}
```
## Docs
<a name="docs"> <a/>

### Overview
The Engine effectivly consists of [Shapes](#shape), and the [Scene](#scene). A `Shape` is anything that can be drawn.
Shapes will only be drawn if they are in the [Scene](#scene). Shapes and [Objects](#object) are added to the Scene
via the [Scene::addChild](#scene) method. Once a Shape or Object is added to the scene it can recieve a number of callbacks.
When these callbacks are called depend on what callback they are, but the most straightforward one to talk about is
the [Object::update](#object) callback. If your class overrides this method, then it will be called every frame. An
example of how you might use that is a [Triangle](#triangle) that moves down 10 pixles every frame.
```C++

class MovingTriangle : public TriangleIsosceles {
	public:
		MovingTriangle(): TriangleIsosceles() {
			this->setPosition(100, 10);
		}

		update() override {
			this->translate(0, -10); // called every frame
		}

}

int main() {
	Game g;
	g.scene->addChild(new MovingTriangle());
	g.run();
}
```
A list of every overrideable callback can be found [here](#callbacks)

### Classes
<a name="classes" />

This is a list of every class in the engine that is note worthy for users of the engine. I.e. this isn't documentation
for people who want to modify engine code. You'll have to read the code for that!

#### Object
<a name="object" />

This is the base class for every object in the game. 

##### Constructors

* [Object()](#object-default)
* [Object(double x, double y)](#object-doubles);
* [Object(Point pos)](#object-point);


##### Properties

[Position](#position) pos


##### Methods
void [kill](#object-kill)()
Object* [getParent](#object-get-parent)()
virtual void [update](#object-update)()
virtual void [onAdd](#object-on-add)()
virtual void [onRemove](#object-on-remove)()
virtual void [onKill](#object-on-kill)()
virtual void [onKeyPress](#object-on-key-press)(Kb::Key key, Input::Action action);
virtual void [onMouseClick](#object-on-mouse-click)(Mouse::Btn btn, Input::Action action);
virtual void [setPosition](#object-set-position)(float x, float y);
virtual void [setPosition](#object-set-position)(Point pos);
void [translate](#object-translate)(float x, float y);



###### Object::Object()
<a name="object-default" />
Constructs a default Object with a position of 0, 0



###### Object::Object(double x, double y)
<a name="object-doubles" />
Constructs an Object with a position with whatever passed in x and y



###### Object::Object(Point pos)
<a name="object-point" />
Constructs an Object with a position of whatever passed in Point





#### Shape
<a name="shape" />





#### Scene
<a name="scene" />




#### Position
<a name="position" />














## FAQ
<a name="faq" />

FAQ is probably misleading because none of these questions have actually been asked of me, they are just questions that
would probably come to my mind when reading about a game engine.



<a name="who"></a>

#### Who Is It For?
This Engine is targeted primarily towards people who want to learn C++, and would like to do so graphically,
but also don't want to learn a giant game engine.



<a name="shouldi"></a>

#### Why Should I Use This?
You probably shouldn't. This engine is a toy intended for drawing shapes easily in C++. If you want to make a real game I would
personally recommend [Godot](https://godotengine.org/). If you just want to draw some shapes using C++ and aren't
worried about performance, or shipping a game then this might be for you.


<a name="why"></a>

#### Why Did You Make This?
Why write a game engine? Good question. There isn't a good reason.
There are about [a million game engines](https://en.wikipedia.org/wiki/List_of_game_engines)
and they are all probably better and faster than this one and a few are open source.
But I wrote this game engine as a learning experience for myself. I wanted to learn C++ and OpenGL. To that end I consider
it a success. I am by no means a master of either, but I know more than when I started.
