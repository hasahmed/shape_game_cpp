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
	  * [Object](#object)
	  * [Shape](#shape)
	  * [MultiShape](#multishape)
	  * [Scene](#scene)
	  * [Position](#position)
  * [Input](#input)
	  * [Action](#action)
	  * [Keyboard](#keyboard)
		  * [Key](#keyboard-key)
		  * [Keyboard Map](#keyboard-map)
	  * [Mouse](#mouse)
		  * [Btn](#mouse-btn)
		  * [Mouse Map](#mouse-map)
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
The Engine effectivly consists of [Shapes](#shape), [MultiShapes](#multishape) and the [Scene](#scene).
A `Shape` is anything that can be drawn. A `MultiShape` is simple a class that glues multiple `Shapes` together.
`MultiShape` act exactly like `Shapes` other than that aspect. For that reason from here on out they will both simply
be refered to as `Shapes`. When something applies to only one or the other that will be stated explicitly.
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

[Position](#position) [pos](#object-pos)


##### Methods
* void [kill](#object-kill)()
* Object* [getParent](#object-get-parent)()
* virtual void [update](#object-update)()
* virtual void [onAdd](#object-on-add)()
* virtual void [onRemove](#object-on-remove)()
* virtual void [onKill](#object-on-kill)()
* virtual void [onKeyPress](#object-on-key-press)(Kb::Key key, Input::Action action);
* virtual void [onMouseClick](#object-on-mouse-click)(Mouse::Btn btn, Input::Action action);
* virtual void [setPosition](#object-set-position)(float x, float y);
* virtual void [setPosition](#object-set-position-point)(Point pos);
* void [translate](#object-translate)(float x, float y);


##### Constructor Details

##### Object::Object()
<a name="object-default" />
Constructs a default Object with a position of 0, 0

##### Object::Object(double x, double y)
<a name="object-doubles" />
Constructs an Object with a position with whatever passed in x and y

##### Object::Object(Point pos)
<a name="object-point" />
Constructs an Object with a position of whatever passed in Point



##### Property Details

##### Object::pos
<a name="object-pos" />

The position of the object. This determines where the object is located on the x, y axes.
For the most part this doesn't matter for the [Object](#object) class. It starts to matter when dealing with things that are
actually going to be drawn i.e. [Shape](#shape) and [MultiShape](#multishape)


##### Method Details

###### void kill()
<a name="object-kill" />

Calling this method will queue and object to be removed from the [Scene](#scene) when it is safe to do so.


###### virtual void update()
<a name="object-update" />

if overridden this method will be called every frame

###### virtual void onAdd()
<a name="object-on-add" />

if overridden this method will be called right after the object is added to the [Scene](#scene)

###### virtual void onRemove()
<a name="object-on-remove" />

if overridden this method will be called right after the object is added to the [Scene](#scene)

###### virtual void onKill()
<a name="object-on-kill" />

if overridden this method will be called right after the object is removed from the [Scene](#scene)


###### virtual void onKeyPress(Kb::Key key, Input::Action action)
<a name="object-on-key-press" />

if overridden this method will be called when a key is pressed. The Key will be passed in along with the action.

##### virtual void onMouseClick(Mouse::Btn btn, Input::Action action)
<a name="object-on-mouse-click" />

if overridden this method will be called the mouse is clicked. The mouse button that was clicked will be passed
to the method along with the action

##### Object* getParent()
<a name="object-get-parent" />
This will return a pointer to the Objects parent. An Object will only have a parent if it is a child of a [MulitShape](#multishape).
Otherwise it will simply return null.


##### void setPosition(float x, float y);
<a name="object-set-position" />

Sets the [pos](#object-pos) property of the object to x and y.

##### void setPosition(Point pos);
<a name="object-set-position-point" />

Sets the [pos](#object-pos) property of the object to pos.

##### void translate(float x, float y);
<a name="object-translate" />

Moves the object from its current position x, and y pixels on their respective axes.



#### Shape
<a name="shape" />
Needs docs



#### Scene
<a name="scene" />
Needs docs



#### Position
<a name="position" />
Needs Docs



#### MultiShape
<a name="multishape" />
Needs Docs




### Input
<a name="input" />
Needs Docs

#### Keyboard
<a name="keyboard" />
Needs Docs

##### Key
<a name="keyboard-key" />
Needs Docs

#### Mouse
<a name="mouse" />
Needs Docs

##### Btn
<a name="mouse-btn" />
Needs Docs





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
