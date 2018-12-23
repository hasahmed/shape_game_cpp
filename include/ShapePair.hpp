#pragma once
#include "Shape.hpp"
namespace shapegame {
	class ShapePair {
		public:
			Shape *first;
			Shape *second;
			ShapePair();
			ShapePair(Shape *first, Shape *second);
      bool operator==(const ShapePair &other) const;
	};
}
namespace std {
	using namespace shapegame;
  template <>
  struct hash<ShapePair> {
    std::size_t operator()(const ShapePair& shapePair) const {
      using std::size_t;
      using std::hash;
      using std::string;
      return (hash<Shape*>()(shapePair.first)) + (hash<Shape*>()(shapePair.second));
    }
  };
}