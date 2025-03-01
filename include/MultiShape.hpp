#pragma once
#include <vector>
#include "Position.hpp"
#include "Entity.hpp"

namespace shapegame {
	class Scene;
	class VetexGenerator;
	class MultiShape : public Entity {
		friend class Scene;
		friend class VertexGenerator;
		private:
			// for public access via getShapes
			std::vector<Object*> shapes;
			// for storing of the memory
			std::vector<std::unique_ptr<Object>> shapeStorage; 
			bool updateSize(Object &obj);
			std::vector<Object*> unAddedObjects;
			bool hasUnaddedObjects = false;
		public:
			virtual ~MultiShape();
			MultiShape();
			MultiShape(Position pos);
			bool removeShape(Object* obj);
			void addShape(Object* obj);
			void addShape(std::unique_ptr<Object> obj);
			std::vector<Object*>& getShapes();
			void setPosition(float x, float y) override;
			void setPosition(Point pos) override;
	};
}
