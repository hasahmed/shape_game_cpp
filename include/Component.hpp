#pragma once
namespace shapegame {
	class Entity;
	class Component {
	public:
		virtual ~Component();
		virtual void update(Entity *ent);
	};
}