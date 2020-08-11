#pragma once
#include <iostream>
namespace shapegame {
	class Point {
		public:
			float x;
			float y;
			virtual ~Point();
			Point();
			Point(float x, float y);
			float getX() const;
			float getY() const;
			virtual void setX(const float x);
			virtual void setY(const float y);
			bool operator==(const Point& rhs);
	};
}
std::ostream& operator<< (std::ostream& stream, const shapegame::Point& rObj);