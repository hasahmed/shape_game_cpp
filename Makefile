CXX=c++
INC_DIR=-Iglad/include
CXXFLAGS=-std=c++17 -g $(INC_DIR)
LDFLAGS= `pkg-config --libs glfw3` -ldl
EXE=main
DIST_NAME=shape-game.a


SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)

all: objs

run: all
	./$(EXE)

objs: $(OBJS) glad.o
	$(CXX) -o $(EXE) $^ $(LDFLAGS)


glad-obj:
	$(CXX) $(CXXFLAGS) -c -o glad.o glad/src/glad.c



.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf main.dSYM
	@echo "Done cleaning"

