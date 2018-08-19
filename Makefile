CXX=c++
INC_DIR=-Iglad/include
CXXFLAGS=-std=c++17 -g $(INC_DIR)
LDFLAGS= `pkg-config --libs lglfw3` -ldl
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

