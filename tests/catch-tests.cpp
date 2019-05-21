#define CATCH_CONFIG_MAIN
#include "include/catch.hpp"
#include "../shapegame"
using namespace shapegame;

class TwoTri : public MultiShape {
	public:
		TwoTri(): MultiShape(Position()) {
			this->addShape(std::make_unique<Triangle>(Position(0, 0), Point(10, 10), Point(11, 11)));
			this->addShape(std::make_unique<Triangle>(Position(0, 0), Point(10, 10), Point(11, 11)));
		}
};

TEST_CASE("MultiShape Parent Checks", "[TwoTri]") {
	auto t = std::make_unique<TwoTri>();
	REQUIRE(t->getShapes().size() == 2);
	REQUIRE(t->getShapes().at(0)->getParent() == t.get());
	REQUIRE(t->getShapes().at(1)->getParent() == t.get());
	REQUIRE(t->removeShape(t->getShapes().at(1)) == true);
	REQUIRE(t->getShapes().size() == 1);
	REQUIRE(t->removeShape(nullptr) == false);
	REQUIRE(t->getShapes().size() == 1);
}