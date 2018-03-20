CC=c++
CFLAGS=-std=c++17 -c -g
LDFLAGS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -g
EXE=main
DIST_NAME=shape-game.a


SRC=$(wildcard *.cpp)
OBJS=$(src:.cpp=.o)

main: $(OBJS)

#dist:


clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf main.dSYM
	@echo "Done cleaning"

