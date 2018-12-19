#include "shapegame"
#include <vector>
#include <cmath>



using namespace shapegame;

CollisionTree::CollisionTree(int depth, int shapeReserve): shapeReserve(shapeReserve) {
	const int numNodes = pow(depth, SCREEN_DIVIDES_PER_STEP);
	this->nodes = std::make_unique<CollNode[]>(numNodes);
	this->root = &(nodes[0]);

	// std::cout << numNodes / SCREEN_DIVIDES_PER_STEP << std::endl;
	// std::cout << (numNodes / SCREEN_DIVIDES_PER_STEP) * 4 << std::endl;
	// std::cout << numNodes << std::endl;

	int nodesPerQuad = numNodes / SCREEN_DIVIDES_PER_STEP;
	int tlOffset = 0;
	int trOffset = nodesPerQuad;
	int blOffset = nodesPerQuad * 2;
	int brOffset = nodesPerQuad * 3;

	std::cout << tlOffset + trOffset + blOffset + brOffset << std::endl;
	std::cout << trOffset << std::endl;
	std::cout << blOffset << std::endl;
	std::cout << brOffset << std::endl;

	// pointers top left
	for(int i = 0; i < nodesPerQuad - 1; i++) {
		this->nodes[i + tlOffset].tl = &(this->nodes[i + tlOffset + 1]);
	}
	// pointers top right
	for(int i = 0; i < trOffset - 1; i++) {
		this->nodes[i].tr = &(this->nodes[i + 1]);
	}

}
CollisionTree::CollisionTree(): CollisionTree(DEFAULT_DEPTH, DEFAULT_RESERVE) {}