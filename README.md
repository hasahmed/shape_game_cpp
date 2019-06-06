# Shapegame
A simple 2D Game Engine for Drawing Shapes In C++

<a name="motivation"></a>
# Motivation
Want to quickly draw some shapes without learning an entire game engine? This aims to be that. Minimal shape drawing in C++.


## Table of Contents
* [Motivation](#motivation)
* [Quick Start](#quickstart)
* [Supported Platforms](#supported-platforms)
* [Set Up](#set-up)
* [Docs](#docs)
  * [Overview](#overview)
  * [Classes](#classes)
	  * [Object](#object)
	  * [Shape](#shape)
	  * [Triangle](#triangle)
	  * [MultiShape](#multishape)
	  * [Entity](#shape)
	  * [Component](#shape)
	  * [Color](#color)
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
<a name="classes"></a>

This is a list of every class in the engine that is note worthy for users of the engine. I.e. this isn't documentation
for people who want to modify engine code. You'll have to read the code for that!

### Object
<a name="object"></a>

This is the base class for every object in the game. 

### Object Constructors

* [Object()](#object-default)
* [Object(double x, double y)](#object-doubles);
* [Object(Point pos)](#object-point);


### Object Properties

[Position](#position) [pos](#object-pos)



### Object Methods
* void [kill](#object-kill)()
* [Object](#object)* [getParent](#object-get-parent)()
* virtual void [update](#object-update)()
* virtual void [onAdd](#object-on-add)()
* virtual void [onRemove](#object-on-remove)()
* virtual void [onKill](#object-on-kill)()
* virtual void [onKeyPress](#object-on-key-press)([Kb::Key](#keyboard-key) key, [Input::Action](#action) action);
* virtual void [onMouseClick](#object-on-mouse-click)([Mouse::Btn](#mouse-btn) btn, [Input::Action](#action) action);
* virtual void [setPosition](#object-set-position)(float x, float y);
* virtual void [setPosition](#object-set-position-point)([Point](#point) pos);
* void [translate](#object-translate)(float x, float y);


### Object Constructor Details

<a name="object-default"></a>

### Object::Object()
Constructs a default Object with a position of 0, 0

<a name="object-doubles"></a>

### Object::Object(double x, double y)
Constructs an Object with a position with whatever passed in x and y

<a name="object-point"></a>

### Object::Object(Point pos)
Constructs an Object with a position of whatever passed in Point



### Object Property Details



<a name="object-pos"></a>

### Object::pos

The position of the object. This determines where the object is located on the x, y axes.
For the most part this doesn't matter for the [Object](#object) class. It starts to matter when dealing with things that are
actually going to be drawn on the screen i.e. [Shape](#shape) and [MultiShape](#multishape)


### Object Method Details


<a name="object-kill"></a>

### void kill()
Calling this method will queue and object to be removed from the [Scene](#scene) when it is safe to do so.


<a name="object-update"></a>

### virtual void update()
if overridden this method will be called every frame

<a name="object-on-add"></a>

### virtual void onAdd()
if overridden this method will be called right after the object is added to the [Scene](#scene)

<a name="object-on-remove"></a>

### virtual void onRemove()
if overridden this method will be called right after the object is added to the [Scene](#scene)

<a name="object-on-kill"></a>

### virtual void onKill()
if overridden this method will be called right after the object is removed from the [Scene](#scene)


<a name="object-on-key-press"></a>

### virtual void onKeyPress(Kb::Key key, Input::Action action)
if overridden this method will be called when a key is pressed. The Key will be passed in along with the action.

<a name="object-on-mouse-click"></a>

### virtual void onMouseClick(Mouse::Btn btn, Input::Action action)
if overridden this method will be called the mouse is clicked. The mouse button that was clicked will be passed
to the method along with the action

<a name="object-get-parent"></a>

### Object* getParent()
This will return a pointer to the Objects parent. An Object will only have a parent if it is a child of a [MulitShape](#multishape).
Otherwise it will simply return null.


<a name="object-set-position"></a>

### void setPosition(float x, float y);
Sets the [pos](#object-pos) property of the object to x and y.

<a name="object-set-position-point"></a>

### void setPosition(Point pos);
Sets the [pos](#object-pos) property of the object to pos.


<a name="object-translate"></a>
### void translate(float x, float y);
Moves the object from its current position x, and y pixels on their respective axes.



<a name="shape"></a>
### *Shape* Extends [Entity](#entity)

Shape class won't actually ever be used directly by the user of this library. It is mostly a wrapper around the TRUE
base class for every drawable object in this engine. The [Triangle](#triangle)

### Shape Properties
[Color](#color) [color](#shape-color)

### Shape Property Details

<a name="shape-color"></a>
### *Shape*::color
The color property of the shape. Determines what color it is a drawn as on the screen. Is of type [Color](#color)

<a name="triangle"></a>

### *Triangle* Extends [Shape](#Shape)

Everything in computer graphics is all about triangles. This engine is no different. This is the shape that makes
up all other shapes by combining them in [MultiShapes](#multishape)

### *Triangle* Constructors
* [Triangle](#triangle-pos)([Position](#position) first, [Point](#point) second, [Point](#point) third);
* [Triangle](#triangle-color)([Position](#position) first, [Point](#point) second, [Point](#point) third, [Color](#color) color);

### *Triangle* Properties

It should be noted that there is no property in triangle called `first` to accompany `second` and `third` because
the [pos](#object-pos) property of [Object](#object) is used instead.

* [Point](#point) [second](#triangle-second)
* [Point](#point) [third](#triangle-third)


### *Triangle* Constructor Details


<a name="triangle-pos"></a>

### *Triangle*::Triangle([Position](#position) first, [Point](#point) second, [Point](#point) third);

Constructs a Triangle object whose points are at the locations specified by the first, second, and third arguments.
It should be noted that triangles points are placed onto the screen in a clockwise manner.


<a name="triangle-color"></a>

### *Triangle*::Triangle([Position](#position) first, [Point](#point) second, [Point](#point) third, [Color](#color) color);

Same as constructor [above](#triangle-pos), but accepts a [Color](#color) argument to set the color of the triangle.


### *Triangle* Property Details

<a name="triangle-second"></a>

### *Triangle*::second

This property of the triangle specifies where the 2nd point of the triangle will be placed on the x, y axes.
It should be noted that triangles points are placed onto the screen in a clockwise manner. It should also be noted
that the [Object::pos](#object-pos) property represents the first point of the triangle.

<a name="triangle-third"></a>

### *Triangle*::third

Same as [Triangle::second](#triangle-second) except the 3rd point to be placed.


<a name="multishape"></a>

### MultiShape

MultiShape's are just like regular shapes, except they allow you to combine multiple [Objects](#object) together in a
nice package via the [addShape](#multishape-add-shape-raw). As stated in the [Triangle](#triangle) docs, this is the class that is used to make every shape that
ships with the engine other than [Triangle](#triangle). In reality MultiShape probably isn't the best name because
regular [Objects](#object) can be added to [MultiShapes](#multishape) as well.


### MultiShape Constructors

* [MultiShape](#multishape-pos)([Position](#position) pos);


### MultiShape Methods

* bool [removeShape](#multishape-remove-shape)([Object](#object)* obj);
* void [addShape](#multishpae-add-shape-raw)([Object](#object)* shape);
* void [addShape](#multishape-add-shape-smart)(std::unique_ptr<[Object](#object)> shape);
* std::vector<[Object](#object)*>& [getShapes](#multishape-get-shapes)();


### MultiShape Constructor Details


<a name="multishape-pos"></a>

### *MultiShape*::MultiShape([Position](#position) pos);

Constructs a [MultiShape](#multishape) at the given position pos.


### MultiShape Method Details


<a name="multishape-remove-shape"></a>

### *MultiShape*::removeShape([Object](#object) obj);

This removes an object specified by a pointer to that object from the [MultiShapes](#muiltishape)
children.
*Note* This method is named poorly. Despite being named as though it only operates on shapes, it operates on [Objects](#object)
and any class derived from that.


<a name="multishape-add-shape-raw"></a>

### void *MultiShape*::addShape([Object](#object) *obj);

Adds a child shape to this multishape, and takes over the memory of the object passed in. The MultiShape is now responsible
for whatever memory is given to it. It creates a smart pointer out of it, and that is freed when the MultiShape is.


<a name="multishape-add-shape-smart"></a>

### void *MultiShape*::addShape(std::unique_ptr<[Object](#object)> obj)

Adds a child shape to this multishape.


<a name="multishape-get-shapes"></a>

### std::vector<[Object](#object)*>& *MultiShape*::getShapes()

Returns a vector of pointers to the shapes that are currently a child of the [MultiShape](#multishape)


<a name="scene"></a>

### Scene

The scene is the container for every object that you want to be a part of your game. When an [Object](#object) is in the
the scene, all of its overloaded [callbacks](#callbacks) are called at the appropriate times. The scene also owns the
memory of all of its containing objects. It handles freeing them when the program ends, as well as when they are
[killed](#object-kill).

### Scene Methods
* [Object](#object)* [addChild](#scene-add-child-raw)([Object](#object) *obj);
* [Object](#object)* [addChild](#scene-add-child-smart)(std::unique_ptr<[Object](#object)> obj);
* template <class T> T* [addChildAs](#scene-add-child-as)(T uniqueShape){
* void [setBackgroundColor](#scene-set-background-color)([Color](#color)& color);


### Scene Method Details

<a name="scene-add-child-raw"></a>

### [Object](#object)* [addChild](#scene-add-child-raw)([Object](#object) *obj);
Adds a obj to the scene, as well as takes control of the memory of the obj. A pointer to the object is returned.
Once added to the scene the obj has all of its overriden [callbacks](#callbacks) called at the appropriate times.


<a name="scene-add-child-smart"></a>

### [Object](#object)* [addChild](#scene-add-child-smart)(std::unique_ptr<[Object](#object)> obj);
Same as [addChild](#scene-add-child-raw) above, but excepts a smart pointer. Still returns a raw pointer to the object.

<a name="scene-add-child-as"></a>

### template <class T> T* [addChildAs](#scene-add-child-as)(T uniqueShape){
Same as [addChild](#scene-add-child-smart) except also has a template argument for what the returned pointer should be
cast to. This is convenient for being able to construct and add an object to the scene and assigne it to a variable in
the same line. Returns a raw pointer to the object cast to type T.
E.g.
```C++
#include <iostream>
#include "shapegame.hpp"

using namespace shapegame;

class Car : public Triangle {
	public:
		Car(): Triangle() {}
		void honk(){
			std::cout << "BEEP BEEP" << std::endl;
		}
};
int main() {
	Game game;
	auto car = game.scene->addChildAs<Car>(std::make_unique<Car>());
	car->honk();
	game.run();
}
```


<a name="scene-set-background-color"></a>

### void setBackgroundColor([Color](#color)& color)

Sets the background color of the scene to the value of color.


<a name="entity"></a>

### *Entity* Extends [Object](#object)

This class is the 'Entity' part of the [Entity Component System](https://en.wikipedia.org/wiki/Entity_component_system).
[Shapes](#shape) extend from this class, so its likely that most of the objects you deal with as a user of this engine
will be Entities that you can add [Components](#componenet) to.


### *Entity* Methods
* void [addComponent](#entity-add-component-raw)([Component](#component) *compo);
* void [addComponent](#entity-add-component-smart)(std::unique_ptr<[Component](#component)> compo);


### *Entity* Methods Details

<a name="entity-add-component-raw"></a>

### void addComponent([Component](#component) *compo)

Creates a new smart pointer out of compo and adds it to the Entity.



<a name="entity-add-component-smart"></a>

### void addComponent(std::unique_ptr<[Component](#component)> compo)

Adds compo to the entity.




<a name="component"></a>

### *Component*
Needs Docs


<a name="color"></a>
### Color
Needs docs


<a name="position"></a>

### Position
Needs Docs







<a name="input"></a>

### Input
Needs Docs

<a name="keyboard"></a>

### Keyboard (Kb)
Needs Docs

<a name="keyboard-key"></a>

#### Keyboard Key (Kb::Key)
Needs Docs

<a name="mouse"></a>

### Mouse
Needs Docs

<a name="mouse-btn"></a>

#### Mouse::Btn
Needs Docs



<a name="faq"></a>

## FAQ

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
