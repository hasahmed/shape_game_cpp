UNAME := $(shell uname -s)
CXXFLAGS = -std=c++17 -g
SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)

ifeq ($(UNAME),Linux)
	CXX := c++
	LDFLAGS := `pkg-config --libs glfw3` -ldl
	INC_DIR := -Iglad/include
	CXXFLAGS += $(INC_DIR)
	OBJS += glad.o
endif

ifeq ($(UNAME),Darwin)
	CXX := c++-7
	LDFLAGS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -g
endif

EXE = main
DIST_NAME = shape-game.a


all: objs

run: all
	./$(EXE)

objs: $(OBJS)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)


#linux specific
glad.o:
	$(CXX) $(CXXFLAGS) -c -o glad.o glad/src/glad.c



.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf *.dSYM
	@echo "Done cleaning"

