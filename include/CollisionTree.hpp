#include <memory>

namespace shapegame {
	class CollNode {
		public:
			CollNode *tl = nullptr; // top left
			CollNode *tr = nullptr; // top right
			CollNode *bl = nullptr; // bottom left
			CollNode *br = nullptr;	 // bottom right
			std::vector<Shape*> shapes;
	};

	class CollisionTree {
		private:
			const int shapeReserve;
			static const int DEFAULT_RESERVE = 100;
			static const int DEFAULT_DEPTH = 4;
			static const int SCREEN_DIVIDES_PER_STEP = 4;

			std::unique_ptr<CollNode[]> nodes; //responsible for the memory
		public:
			CollNode *root = nullptr;
			CollisionTree(int depth, int shapeReserve);
			CollisionTree();
	};
}