#pragma once
#include <vector>
#include "Position.hpp"
#include "Entity.hpp"

namespace shapegame {
	class Scene;
	class MultiShape : public Entity {
		friend class Scene;
		private:
			// for public access via getShapes
			std::vector<Object*> shapes;
			// for storing of the memory
			std::vector<std::unique_ptr<Object>> shapeStorage; 
		public:
			virtual ~MultiShape();
			// MultiShape(Object* controller, std::vector<Object*>& shapes);
			MultiShape(Position pos);
			bool removeShape(Object* obj);
			virtual void addShape(Object* shape);
			virtual void addShape(std::unique_ptr<Object> shape);
			std::vector<Object*>& getShapes();
			virtual void onAdd() override;
			virtual void onKill() override;
			virtual void setPosition(float x, float y) override;
			virtual void setPosition(Point pos) override;
	};
}