#include "shapegame"
#include <vector>
#include <cmath>

#define DEFAULT_RESERVE 100
#define DEFAULT_DEPTH 4


using namespace shapegame;

CollisionTree::CollisionTree(int depth, int shapeReserve): shapeReserve(shapeReserve) {
	const int numNodes = pow(depth, 4);
	std::cout << numNodes << std::endl;
	// CollNode[] nodeArr = new[]();
}
CollisionTree::CollisionTree(): CollisionTree(DEFAULT_DEPTH, DEFAULT_RESERVE) {}