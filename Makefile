CC=c++
CFLAGS=-std=c++17 -c -g
LDFLAGS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -g
EXE=main


OBJS=main.o

main: $(OBJS)


clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@echo "Done cleaning"

