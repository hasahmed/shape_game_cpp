#pragma once
#include <GLFW/glfw3.h>
#include <unordered_set>
#include <chrono>
#include <map>
#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
namespace shapegame {
	class CollisionList {
		public:
			/**
			 * Adds to internal store
			 */
			virtual void add(Shape*) = 0;
			/**
			 * Checks every element stored in the list to see if they collide with eachother
			 */
			virtual void check() = 0;
			/**
			 * Clears the internal store
			 */
			virtual void clear() = 0;

			/**
			 * Should remove ALL refrences to given shape
			 */
			virtual void remove(Shape*) = 0;

			virtual ~CollisionList(){
			}
	};
}
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
}namespace shapegame {
    class Color {
        private:
            float _color[4];
        public:
            Color(float red, float green, float blue, float alpha);
            Color(float red, float green, float blue);
            Color();
            float* getRawColor();
            void set(float red, float green, float blue);
            void set(float red, float green, float blue, float alpha);
            void set(Color& c);
            float r;
            float g;
            float b;
            float a;

            static Color BLACK;
            static Color WHITE;
            static Color LIGHT_GRAY;
            static Color GRAY;
						static Color DARK_GRAY;
            static Color RED;
            static Color PINK;
            static Color KATIE_PINK;
            static Color GREEN;
            static Color BLUE_LIGHT;
            static Color BLUE;
            static Color YELLOW;
            static Color PURPLE;
            static Color NIL;
    };
}

namespace shapegame {
	class Entity;
	class Component {
	public:
		virtual ~Component();
		// virtual void translate(Object *ent, float x, float y);
		virtual void update(Entity *ent);
	};
}namespace shapegame {
    class Debug {
    };
}

namespace shapegame {
	class DebugKeyHandler : public Object {
		public: 
		DebugKeyHandler();
		void onKeyPress(Kb::Key key, Input::Action action) override;
	};
}
namespace shapegame {
	class Dirtyable {
		public:
			virtual void setDirty(bool dirty) = 0;
			virtual bool isDirty() = 0;
			virtual ~Dirtyable() = default;
	};
}namespace shapegame {
    class Drawable {
        friend class Scene;
        protected:
            int _vertexAttribIndex;
            GLuint _vao, _vbo;
            float *_verts;
            int _numVerts;
    };
}
namespace shapegame {
	class Entity : public Object {
		public:
		std::vector<std::unique_ptr<Component>> compos;
		Entity(Position pos);
		Entity() = default;
		virtual ~Entity();
		virtual void addComponent(Component *compo);
		virtual void addComponent(std::unique_ptr<Component> compo);
	};
}

namespace shapegame {

    class FileUtil {
        public:
        static std::string read(std::string path);
    };
}


namespace shapegame {
	class Game {
		private:
			std::unique_ptr<IWindow> _window;
			std::unique_ptr<GLHandler> _glHandler;
			std::unique_ptr<VertexGenerator> _vertexGenerator;
			static Game *_inst;
		public:
			std::unique_ptr<Scene> scene;
			Game(
					unsigned int windowWidth,
					unsigned int windowHeight,
					std::string windowTitle
					);
			Game();
			static Game& inst();
			void draw(RenderPackage &rPack);
			void run();
			void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg);
			void terminateRenderObj(RenderPackage &rPack);
			IWindow const* getWindow();
	};
}



namespace shapegame {
    class GLHandler{
			public:
				virtual void setClearColor(Color& color) = 0;
				virtual void run() = 0;
				virtual void draw(RenderPackage &rPack) = 0;
				virtual void terminateRenderObj(RenderPackage &rPack) = 0;
				virtual void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) = 0;
				virtual ~GLHandler() = default;
		};
}

namespace shapegame {
    class GLHandlerImpl : public GLHandler {
        private:
            GLFWwindow *windowHandle;
            GLuint vbo, vao;
            Scene &_scene;
            static int _assignableVertexAttribIndex;
            Color _clearColor;
        public:

            GLuint shader_prog;
            GLHandlerImpl(IWindow *window, Scene &scene);
            //methods
            void check_shader_err(int shader);
            void setClearColor(Color& color) override;
						void terminateRenderObj(RenderPackage &rPack) override;
						void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) override;
            //void cursor_position_callback(GLFWwindow *window, double x, double y);
						void draw(RenderPackage &rPack) override;
            void run() override;
    };
}
#define DEBUG 1
#define PRINT_DESTRUCTION 0
#define GLCHECKERR() _gl_check_error(__FILE__,__LINE__)
#if DEBUG
#define GLCALL(gl_function) do {\
    gl_function;\
    GLCHECKERR();\
} while(0);
#else
#define GLCALL(gl_function) gl_function
#endif
namespace shapegame {
    void _gl_check_error(const char *file, int line);
    enum class ShapeType {
        Triangle,
        Rectangle,
        Circle,
				Multi
    };
    class Globals {
			public:
				static double dt;
				static double fps;
    };
	typedef Globals G; //alias
}

namespace shapegame {
    class GLRenderObject {
        public:
            int vertexAttribIndex;
            GLuint vao;
            GLuint vbo;
						GLuint shaderProg;
            float verts[9];
						int numVerts = 9;
            GLRenderObject(Shape &s, GLuint shaderProg);
						GLRenderObject() = default;
    };
}
std::ostream& operator<< (std::ostream& stream, const shapegame::GLRenderObject& rObj);
namespace shapegame {
	namespace Input {
		enum class Action {
			DOWN = GLFW_PRESS,
			UP = GLFW_RELEASE,
			REPEATE = GLFW_REPEAT
		};
		class Mouse {
			public:
			enum class Btn {
				LEFT = GLFW_MOUSE_BUTTON_LEFT,
				RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
				MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
				N1 = GLFW_MOUSE_BUTTON_1,
				N2 = GLFW_MOUSE_BUTTON_2,
				N3 = GLFW_MOUSE_BUTTON_3,
				N4 = GLFW_MOUSE_BUTTON_4,
				N5 = GLFW_MOUSE_BUTTON_5,
				N6 = GLFW_MOUSE_BUTTON_6,
				N7 = GLFW_MOUSE_BUTTON_7,
				N8 = GLFW_MOUSE_BUTTON_8
			};
			static Position pos();
		};
		class Kb {
			public:
			enum class Key {
				SPACE = GLFW_KEY_SPACE,
				APOSTROPHE = GLFW_KEY_APOSTROPHE,
				COMMA = GLFW_KEY_COMMA,
				MINUS = GLFW_KEY_MINUS,
				PERIOD = GLFW_KEY_PERIOD,
				SLASH = GLFW_KEY_SLASH,
				N0 = GLFW_KEY_0,
				N1 = GLFW_KEY_1,
				N2 = GLFW_KEY_2,
				N3 = GLFW_KEY_3,
				N4 = GLFW_KEY_4,
				N5 = GLFW_KEY_5,
				N6 = GLFW_KEY_6,
				N7 = GLFW_KEY_7,
				N8 = GLFW_KEY_8,
				N9 = GLFW_KEY_9,
				SEMICOLON = GLFW_KEY_SEMICOLON,
				EQUAL = GLFW_KEY_EQUAL,
				A = GLFW_KEY_A,
				B = GLFW_KEY_B,
				C = GLFW_KEY_C,
				D = GLFW_KEY_D,
				E = GLFW_KEY_E,
				F = GLFW_KEY_F,
				G = GLFW_KEY_G,
				H = GLFW_KEY_H,
				I = GLFW_KEY_I,
				J = GLFW_KEY_J,
				K = GLFW_KEY_K,
				L = GLFW_KEY_L,
				M = GLFW_KEY_M,
				N = GLFW_KEY_N,
				O = GLFW_KEY_O,
				P = GLFW_KEY_P,
				Q = GLFW_KEY_Q,
				R = GLFW_KEY_R,
				S = GLFW_KEY_S,
				T = GLFW_KEY_T,
				U = GLFW_KEY_U,
				V = GLFW_KEY_V,
				W = GLFW_KEY_W,
				X = GLFW_KEY_X,
				Y = GLFW_KEY_Y,
				Z = GLFW_KEY_Z,
				LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
				BACKSLASH = GLFW_KEY_BACKSLASH,
				RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
				GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
				WORLD_1 = GLFW_KEY_WORLD_1,
				WORLD_2 = GLFW_KEY_WORLD_2,
				ESCAPE = GLFW_KEY_ESCAPE,
				ENTER = GLFW_KEY_ENTER,
				TAB = GLFW_KEY_TAB,
				BACKSPACE = GLFW_KEY_BACKSPACE,
				INSERT = GLFW_KEY_INSERT,
				DELETE = GLFW_KEY_DELETE,
				RIGHT = GLFW_KEY_RIGHT,
				LEFT = GLFW_KEY_LEFT,
				DOWN = GLFW_KEY_DOWN,
				UP = GLFW_KEY_UP,
				PAGE_UP = GLFW_KEY_PAGE_UP,
				PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
				HOME = GLFW_KEY_HOME,
				END = GLFW_KEY_END,
				CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
				SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
				NUM_LOCK = GLFW_KEY_NUM_LOCK,
				PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
				PAUSE = GLFW_KEY_PAUSE,
				F1 = GLFW_KEY_F1,
				F2 = GLFW_KEY_F2,
				F3 = GLFW_KEY_F3,
				F4 = GLFW_KEY_F4,
				F5 = GLFW_KEY_F5,
				F6 = GLFW_KEY_F6,
				F7 = GLFW_KEY_F7,
				F8 = GLFW_KEY_F8,
				F9 = GLFW_KEY_F9,
				F10 = GLFW_KEY_F10,
				F11 = GLFW_KEY_F11,
				F12 = GLFW_KEY_F12,
				F13 = GLFW_KEY_F13,
				F14 = GLFW_KEY_F14,
				F15 = GLFW_KEY_F15,
				F16 = GLFW_KEY_F16,
				F17 = GLFW_KEY_F17,
				F18 = GLFW_KEY_F18,
				F19 = GLFW_KEY_F19,
				F20 = GLFW_KEY_F20,
				F21 = GLFW_KEY_F21,
				F22 = GLFW_KEY_F22,
				F23 = GLFW_KEY_F23,
				F24 = GLFW_KEY_F24,
				F25 = GLFW_KEY_F25,
				KP_0 = GLFW_KEY_KP_0,
				KP_1 = GLFW_KEY_KP_1,
				KP_2 = GLFW_KEY_KP_2,
				KP_3 = GLFW_KEY_KP_3,
				KP_4 = GLFW_KEY_KP_4,
				KP_5 = GLFW_KEY_KP_5,
				KP_6 = GLFW_KEY_KP_6,
				KP_7 = GLFW_KEY_KP_7,
				KP_8 = GLFW_KEY_KP_8,
				KP_9 = GLFW_KEY_KP_9,
				KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
				KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
				KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
				KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
				KP_ADD = GLFW_KEY_KP_ADD,
				KP_ENTER = GLFW_KEY_KP_ENTER,
				KP_EQUAL = GLFW_KEY_KP_EQUAL,
				LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
				LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
				LEFT_ALT = GLFW_KEY_LEFT_ALT,
				LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
				RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
				RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
				RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
				RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
				MENU = GLFW_KEY_MENU
			};
			static bool down(Key key);
			static bool up(Key key);
		};
	} // namespace Input
} // namespace shapegame
struct GLFWwindow;

namespace shapegame {
	class IWindow {
		public:
			virtual GLFWwindow* getWindowHandle() const = 0;
			virtual int getHeight() = 0;
			virtual int getWidth() = 0;
			virtual ~IWindow() = default;
	};
} // shapegame

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
			void setPosition(float x, float y) override;
			void setPosition(Point pos) override;
	};
}

namespace shapegame { 
	class NullRenderer : public GLHandler {
		private:
			Scene &scene;
		public:
			NullRenderer(Scene &scene);
			void setClearColor(Color& color) override;
			void run() override;
			void draw(RenderPackage &rPack) override;
			void initRenderObj(GLRenderObject &rObj, Shape &shape, GLuint shaderProg) override;
			virtual ~NullRenderer() = default;
	};
} // namespace shapegame


namespace shapegame {
	class NullWindow : public IWindow{
			GLFWwindow* getWindowHandle() const override;
			int getHeight() override;
			int getWidth() override;
	};
	
} // shapegamenamespace shapegame {
	using namespace Input;
    class Object : public Dirtyable {
			friend class Scene;
			friend class Position;
			friend class MultiShape;
			private:
				bool canKill = false;
				bool _dirty = false;
				bool _inScene = false;
				Object *_parent = nullptr;
				void setParent(Object *parent);
			public:
				std::string name = "Object";
				Position pos;
				Object();
				Object(double x, double y);
				Object(Point pos);
				void kill();
				Object* getParent();
				virtual ~Object();
				virtual void update();
				virtual void onAdd();
				virtual void onRemove(); //called on removal
				virtual void onKill(); //called as soon as kill is called
				virtual void onKeyPress(Kb::Key key, Input::Action action);
				virtual void onMouseClick(Mouse::Btn btn, Input::Action action);
				virtual void setPosition(float x, float y);
				virtual void setPosition(Point pos);
				void translate(float x, float y);
				bool isInScene();
				void setDirty(bool dirty) override;
				bool isDirty() override;
    };
}
namespace shapegame {
	class Point {
		public:
			float x;
			float y;
			virtual ~Point();
			Point();
			Point(float x, float y);
			virtual float getX() const;
			virtual float getY() const;
			virtual void setX(const float x);
			virtual void setY(const float y);
	};
}


namespace shapegame {
    class Position : public Point {
			friend class Object;
			private:
			public:
				Dirtyable *owner_;
				Position(float x, float y, Dirtyable *owner);
				Position(Point pos, Dirtyable *owner);
				Position(Dirtyable *owner);



				Position(float x, float y);
				Position(Point pos);
				Position();
				virtual void setX(const float x) override;
				virtual void setY(const float y) override;
    };
}
namespace shapegame {
	class Quad : public MultiShape {
		public:
		using MultiShape::MultiShape;
		Quad(Position p1, Point p2, Point p3, Point p4, Color color);
		virtual ~Quad() = default;
	};
}


namespace shapegame {
	class Rectangle : public MultiShape {
		public:
			virtual ~Rectangle();
			Rectangle(float width, float height, Position pos, Color color);
	};
}
namespace shapegame {
	class RenderPackage {
		public:
			Shape& shape; // Scene owns this Shape object
			std::unique_ptr<GLRenderObject> glRenderObject; // this should be more generic so that
			// the type of render object it holds could be arbitrary for other rendering systems
			~RenderPackage();
			RenderPackage(const RenderPackage &rPack); //copy ctor
			// RenderPackage(RenderPackage &&rPack); //move ctor
			RenderPackage(Shape &shape, GLRenderObject &glRenderObject);
			// void draw();
			bool updateDirty();
	};
}


namespace shapegame {

	/*
		Wraps objects in with the components needed to render them
	*/
	struct ObjRenderWrapper {
		std::unique_ptr<Object> obj;
		std::vector<RenderPackage> rPacks;
		ObjRenderWrapper(std::unique_ptr<Object> pObj): obj(std::move(pObj)) {}
		ObjRenderWrapper(std::unique_ptr<Object> pObj, RenderPackage* rPack): ObjRenderWrapper(std::move(pObj)) {
			this->rPacks.emplace_back(*rPack);
		}
		void addRPack(RenderPackage *rPack) {
			this->rPacks.emplace_back(std::move(*rPack));
		}
	};

	class Scene {
			friend class GLHandlerImpl;
			friend class NullRenderer;
			private:
				Color _bgColor;
				GLuint _shaderProg;
				void setShaderProg(GLuint shaderprog);
				std::vector<Object*> killList;
				std::vector<ObjRenderWrapper> sceneChildren;
				static Scene *_inst;
				void initRenderables(ObjRenderWrapper &owr, Shape &shape);
				void addSubChild(ObjRenderWrapper &owr, Object* subObj);
				void killQueued();
				void drawChild(ObjRenderWrapper &owr);
			public:
				bool shouldCheck = false;
				std::unique_ptr<CollisionList> collisionList;
				void updateChildren();
				void drawChildren();
				Object* addChild(Object *shape);
				Object* addChild(std::unique_ptr<Object> obj);
				void addMultiShapeChild(Object* obj);
				template <class T>
				T* addChildAs(T uniqueShape){
					auto rawPtr = uniqueShape.get();
					this->addChild(std::move(uniqueShape));
					return rawPtr;
				}
				static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void mouseBtnCallback(GLFWwindow* window, int btn, int action, int mods);
				void keyDispatch(int key, int action);
				void mouseBtnDispatch(int btn, int action);
				void setBackgroundColor(Color& color);
				int numChildren();
				Scene();
	};
}
namespace shapegame {


    class ShaderHandler{
    };
}

namespace shapegame {
    class Shape : public Entity {
        friend class Scene;
        friend class RenderPackage;
        protected:
					float _height;
					float _width;
        public:
					bool collidable = false;
					Color color;
					ShapeType type;
					virtual ~Shape();
					Shape(float height, float width, ShapeType type, Color color);
					Shape(float height, float width, ShapeType type, Position pos, Color color);
					float getHeight() const;
					float getWidth() const;
					virtual void onCollisionStart(Shape &other);
					virtual void onCollisionStop(Shape &other);
					virtual void onColliding(Shape &other);
					bool isColliding(Shape &other);
					virtual void translate(float x, float y);
					virtual void translate(Position pos);
    };
}
// std::ostream& operator<< (std::ostream& stream, const shapegame::Shape& shape);#ifndef __MACH__
#endif
#define GLFW_DLL
#define GLFW_INCLUDE_GLCOREARB
namespace shapegame {
	class ShapePair {
		public:
			Shape *first;
			Shape *second;
			ShapePair();
			ShapePair(Shape *first, Shape *second);
      bool operator==(const ShapePair &other) const;
	};
}
namespace std {
	using namespace shapegame;
  template <>
  struct hash<ShapePair> {
    std::size_t operator()(const ShapePair& shapePair) const {
      using std::size_t;
      using std::hash;
      using std::string;
      return (hash<Shape*>()(shapePair.first)) + (hash<Shape*>()(shapePair.second));
    }
  };
}namespace shapegame {
	class SimpleCollision : public CollisionList {
	private:
		std::vector<ShapePair> findContaining(Shape *shape);
	public:
		std::unordered_set<Shape*> shapeStore;
		std::unordered_set<ShapePair> currentlyColliding_;
		SimpleCollision();
		void add(Shape* shape) override;
		void remove(Shape* shape) override;
		void clear() override;
		void check() override;
	};
}
namespace shapegame {
    class Square : Shape {
        private:
        float _verts[18] = {
            //right side triangle
            0.5f,  0.5f, 0.0f,  // top right
            -0.5f, -0.5f, 0.0f,  // bottom left
            0.5f, -0.5f, 0.0f,  // bottom right

            0.5f,  0.5f, 0.0f,  // top right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        };
    };
}
namespace shapegame {
	class Timer : public Object {
		private:
			double milliseconds;
			bool repeates;
			bool autoStart;
			std::function<void(void)> callBack;
			bool killOnComplete;

			// internal state	
			bool _running = false;
			std::chrono::time_point<std::chrono::high_resolution_clock> _timerStart;
			std::chrono::duration<double> _timeElapsed {0};
			std::chrono::milliseconds _msElapsed {0};

		public:
			Timer(double millisecs, bool repeates, bool autoStart, std::function<void(void)> callBack, bool killOnComplete=true);
			~Timer() = default;
			void start();
			void stop();
			void onAdd() override;
			void update() override;
	};
}
namespace shapegame {
	class TreeNode {
	};
	
} // shapegame

namespace shapegame {
    class Triangle : public Shape {
        public:
				using Shape::setPosition;
				Point second; // second point of the triangle
				Point third; // third
				Position collisionPosition;
				virtual ~Triangle();
				Triangle();
				Triangle(Position first, Point second, Point third);
				Triangle(Position first, Point second, Point third, Color color);
				int getNumVerts();
				// void translate(float x, float y) override;
				// void translate(Position pos) override;
				// void setPosition(Position pos);
				virtual void setPosition(float x, float y) override;
    };
}

namespace shapegame {
	class TriangleIsosceles : public Triangle {
		public:
		TriangleIsosceles(float width, float height, Position pos, Color color);
	};
}
namespace shapegame {
    class VertexGenerator {
        friend class Game;
        public:
            static VertexGenerator* instance();
            void generate(const Shape &shape, float *verts);
            VertexGenerator(IWindow *window);
        private:
            static VertexGenerator *_instance;
            IWindow *_window;
            void triangleVerts(const Shape &shape, float *verts);
            float horPxStep();
            float vertPxStep();
            float yPxToGl(float coord);
            float xPxToGl(float coord);
            Point pxToGl(float x, float y);
            Point pxToGl(Point coords);
    };
}
namespace shapegame {

	// class WindowInterface {
	// 	// virtual WindowInterface(int width, int height, std::string title) = 0;
	// 	public:
	// 		virtual int getHeight() = 0;
	// 		virtual int getWidth() = 0;
	// 		virtual std::string infoString() = 0;
	// 		virtual GLFWwindow* getWindowHandle() const = 0;
	// 		virtual WindowInterface* make(int width, int height, std::string title) = 0;
	// };

	class Window : public IWindow {
		private:
			Window(){}
			static Window _instance;
			int _width;
			int _height;
			const GLubyte* gl_renderer;
			const GLubyte* gl_version;
			GLFWwindow* windowHandle;
		public:
			// GLFWwindow* getWindowHandle();
			std::string infoString() ;
			Window(int width, int height, std::string window_title);
			GLFWwindow* getWindowHandle() const override;
			// static Window* getWindow();

			int getHeight() override;
			int getWidth() override;
	};

}
