#pragma once
#include <vector>
#include "Position.hpp"
#include "Entity.hpp"

// class ShapeVector {
// 	private:
// 	bool inScene = false;
// 	std::unique_ptr<std::vector<std::unique_ptr<Object>>> unAddedShapes;
// 	std::unique_ptr<std::vector<Object*>> addedShapes;
// 	public:
// 	void onAdded(){
// 		this->inScene = true;
// 	}
// 	std::vector<Object*>& getShapes() {
// 		if (this->inScene) {
// 			return 
// 		}
// 	}
// };


namespace shapegame {
	class Scene;
	class MultiShape : public Entity {
		friend class Scene;
		private:
		void onMultiAdd();
		std::vector<Object*> shapes;
		std::vector<std::unique_ptr<Object>> unAddedShapes;
		public:
		~MultiShape();
		MultiShape(Object* controller, std::vector<Object*>& shapes);
		MultiShape(Position pos);
		virtual void addShape(Object* shape);
		virtual void addShape(std::unique_ptr<Object> shape);
		virtual void onAdd() override;
		virtual void onKill() override;
		virtual void setPosition(float x, float y) override;
		virtual void setPosition(Point pos) override;
		virtual void setZOrder(int zOrder) override;
	};
}