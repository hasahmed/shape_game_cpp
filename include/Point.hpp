#pragma once
namespace shapegame {
	class Point {
		protected: 
			float _x;
			float _y;
		public:
			virtual ~Point();
			Point();
			Point(float x, float y);
			virtual float getX() const;
			virtual float getY() const;
			virtual void setX(const float x);
			virtual void setY(const float y);
	};
}