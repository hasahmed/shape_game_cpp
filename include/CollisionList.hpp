#pragma once
#include "Shape.hpp"
namespace shapegame {
	class CollisionList {
		public:
			/**
			 * Adds to internal store
			 */
			virtual void add(Shape*) = 0;
			/**
			 * Checks every element stored in the list to see if they collide with eachother
			 */
			virtual void check() = 0;
			/**
			 * Clears the internal store
			 */
			virtual void clear() = 0;
			virtual ~CollisionList(){
			}
	};
}