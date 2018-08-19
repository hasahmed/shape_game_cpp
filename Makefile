CXX=cc
CXXFLAGS=-std=c++17 -g
LDFLAGS= `pkg-config --libs lglfw3` -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -g
EXE=main
DIST_NAME=shape-game.a


SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)

run: main
	./$(EXE)

main: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf main.dSYM
	@echo "Done cleaning"

