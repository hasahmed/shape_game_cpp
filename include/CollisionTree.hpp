#include <memory>

namespace shapegame {
	class CollNode {
		public:
			std::unique_ptr<CollNode> tl = nullptr;
			std::unique_ptr<CollNode> tr = nullptr;
			std::unique_ptr<CollNode> bl = nullptr;
			std::unique_ptr<CollNode> br = nullptr;	
			std::vector<Shape*> shapes;
	};

	class CollisionTree {
		private:
			const int shapeReserve;
		public:
			CollNode head;
			CollisionTree(int depth, int shapeReserve);
			CollisionTree();
	};
}