#include <iostream>
#include <assert.h>
#include "../shapegame"

using namespace shapegame;


int counts = 0;

void traverseTl(CollNode *n){
	if (!n)
		return;
	counts++;
	traverseTl(n->tl);
}
void traverseTr(CollNode *n){
	if (!n)
		return;
	counts++;
	traverseTl(n->tr);
}
void traverseBl(CollNode *n){
	if (!n)
		return;
	counts++;
	traverseTl(n->bl);
}
void traverseBr(CollNode *n){
	if (!n)
		return;
	counts++;
	traverseTl(n->br);
}

int main() {
	CollisionTree c(4, 100);
	traverseTl(c.root->tl);
	assert(counts == 63);
	traverseTr(c.root->tr);
	std::cout << counts << std::endl;
	// assert(counts == 127);
	// std::cout << CollisionTree::DEFAULT_RESERVE << std::endl;
	std::cout << "All gucci" << std::endl;
}