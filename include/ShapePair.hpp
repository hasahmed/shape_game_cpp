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

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return (hash<Shape*>()(shapePair.first)) + (hash<Shape*>()(shapePair.second));
    }
  };
}