CXX=c++
INC_DIR=-Iglad/include
CXXFLAGS=-std=c++17 -g $(INC_DIR)
LDFLAGS= `pkg-config --libs glfw3` -ldl
EXE=main
DIST_NAME=shape-game.a

ecc:
	@echo $(OS)


SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)
OBJS += glad.o

all: objs

run: all
	./$(EXE)

objs: $(OBJS)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)


glad.o:
	$(CXX) $(CXXFLAGS) -c -o glad.o glad/src/glad.c



.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf *.dSYM
	@echo "Done cleaning"

