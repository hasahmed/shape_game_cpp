#pragma once

#include "Point.hpp"
#include "Dirtyable.hpp"


namespace shapegame {
    class Position : public Point {
        private:
					Dirtyable *owner;
				public:
					Position(float x, float y, Dirtyable *owner);
					Position(float x, float y);
					Position(Point pos, Dirtyable *owner);
					Position(Point pos);
					Position(Dirtyable *owner);
					Position();
					virtual void setX(const float x) override;
					virtual void setY(const float y) override;
    };
}