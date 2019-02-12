#pragma once
namespace shapegame {
	class Point {
		public:
			float x;
			float y;
			virtual ~Point();
			Point();
			Point(float x, float y);
			virtual float getX() const;
			virtual float getY() const;
			virtual void setX(const float x);
			virtual void setY(const float y);
	};
}