#pragma once

#include "Point.hpp"
#include "Dirtyable.hpp"


namespace shapegame {
    class Position : public Point {
			friend class Object;
			private:
				Dirtyable *owner_;
				Position(float x, float y, Dirtyable *owner);
				Position(Point pos, Dirtyable *owner);
				Position(Dirtyable *owner);
			public:
				Position(float x, float y);
				Position(Point pos);
				Position();
				void setX(const float x) override;
				void setY(const float y) override;
    };
}