#pragma once
#include <vector>
#include "Position.hpp"
#include "Entity.hpp"

namespace shapegame {
	class Scene;
	class MultiShape : public Entity {
		friend class Scene;
		private:
			void onMultiAdd();
			std::vector<Object*> shapes;
			 /* to protect from memory-leaks in case deleted before being added to the scene */
			std::vector<std::unique_ptr<Object>> unAddedShapes; 
			Object* _parent = nullptr;
		public:
			virtual ~MultiShape();
			MultiShape(Object* controller, std::vector<Object*>& shapes);
			MultiShape(Position pos);
			virtual void addShape(Object* shape);
			virtual void addShape(std::unique_ptr<Object> shape);
			std::vector<Object*>& getChildren();
			Object* getParent();
			virtual void onAdd() override;
			virtual void onKill() override;
			virtual void setPosition(float x, float y) override;
			virtual void setPosition(Point pos) override;
			virtual void setZOrder(int zOrder) override;
	};
}