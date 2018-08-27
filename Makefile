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
MACOS_DIST_NAME = shapegame.dylib
LINUX_DIST_NAME = shapegame.a


all: objs

run: all
	./$(EXE)

objs: $(OBJS)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)


#linux specific
glad.o:
	$(CXX) $(CXXFLAGS) -c -o glad.o glad/src/glad.c


shapegame.dylib: objs
	$(CXX) -std=c++17 -dynamiclib -current_version 0.0.1 -compatibility_version 0.0.1 -undefined suppress -flat_namespace $(OBJS) -o $(MACOS_DIST_NAME)



.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf *.dSYM
	@echo "Done cleaning"

