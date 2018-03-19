CC=c++
#CFLAGS=-std=c++17 -c -g
CFLAGS=-c -g
LDFLAGS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
EXE=main


objs: main.o

main: objs

clean:
	rm -f objs $(EXE)

