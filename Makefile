CC=c++
#CXXFLAGS=-std=c++17 -c -g
CXXFLAGS=-std=c++14 -c -g
LDFLAGS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -g
EXE=main
DIST_NAME=shape-game.a


SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)

main: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

#objs: $(SRC)
	#$(CC) $(CFLAGS) $^


#$(CC) -o $@ $^ $(LDFLAGS)
test:
	@echo $(OBJS)

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf main.dSYM
	@echo "Done cleaning"

