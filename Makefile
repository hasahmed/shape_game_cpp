UNAME := $(shell uname -s)
CXXFLAGS = -std=c++17 -g -Wall
SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)

ifeq ($(UNAME),Linux)
	CXX := c++
	LDFLAGS := `pkg-config --libs glfw3` -ldl
	INC_DIR := -Ideps -Iinclude
	CXXFLAGS += $(INC_DIR)
	OBJS += glad.o
endif

ifeq ($(UNAME),Darwin)
	CXX := c++-7
	LDFLAGS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -g
	INC_DIR := -Iinclude
	CXXFLAGS += $(INC_DIR)
endif

EXE = main
MACOS_DIST_NAME = shapegame.dylib
LINUX_DIST_NAME = shapegame.a
WIN_DIST_NAME = shapegame.dll


all: main

run: all
	./$(EXE)

main: $(OBJS)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)


#linux specific
glad.o:
	$(CXX) $(CXXFLAGS) -c -o glad.o deps/glad.c


shapegame.dylib: objs
	$(CXX) -std=c++17 -dynamiclib -current_version 0.0.1 -compatibility_version 0.0.1 -undefined suppress -flat_namespace $(OBJS) -o $(MACOS_DIST_NAME)



.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE) $(MACOS_DIST_NAME) $(LINUX_DIST_NAME) $(WIN_DIST_NAME)
	@rm -rf *.dSYM
	@echo "Done cleaning"
