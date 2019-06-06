UNAME := $(shell uname -s)
CXXFLAGS = -std=c++17 -Wall -Wno-unused-variable -Wno-unused-private-field
SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:src/%.cpp=obj/%.o)
INC_DIR := -Ideps -Iinclude
GLAD =

ifeq ($(UNAME),Linux)
	CXX := c++
	LDFLAGS += platform/linux/libglfw.so
	CXXFLAGS += $(INC_DIR) -fPIC
	GLAD = obj/glad.o
endif

ifeq ($(UNAME),Darwin)
	CXX := clang++
	LD=clang++
	LDFLAGS += platform/mac/libGL.dylib platform/mac/libGLU.dylib platform/mac/libglfw.3.dylib -framework Cocoa -framework IOKit -framework CoreVideo -g
	LDFLAGS += -L/usr/local/opt/llvm/lib
	CXXFLAGS += $(INC_DIR)
endif

EXE = main
MACOS_DIST_NAME = shapegame.dylib
LINUX_DIST_NAME = shapegame.so
WIN_DIST_NAME = shapegame.dll

all: main.test

run: all
	./$(EXE)

main.test: $(OBJS) $(GLAD) obj/main.test.o
	$(CXX) -o bin/$@ $^ $(LDFLAGS)

add-child-as: $(OBJS) $(GLAD) obj/add-child-as.o
	$(CXX) -o bin/$@ $^ $(LDFLAGS)


prod: CXXFLAGS += -Ofast
prod: main.test

sani: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer -glldb -g -O0 -gfull -g3 -gcolumn-info
sani: LDFLAGS += -L/usr/local/opt/llvm/lib -fsanitize=address -fno-omit-frame-pointer -g
sani: main.test


dbg: CXXFLAGS += -glldb -g -O0 -gfull -g3 -gcolumn-info
dbg: LDFLAGS += -g
dbg: main.test

dbg-run: dbg
	PATH=/usr/bin /usr/bin/lldb ./main.test

deletion.test: $(OBJS) deletion.test.o
	$(CXX) -o $@ $^ $(LDFLAGS)
triangle.test: $(OBJS) triangle.test.o
	$(CXX) -o $@ $^ $(LDFLAGS)


#linux specific
obj/glad.o:
	$(CXX) $(CXXFLAGS) -c deps/glad.c -o obj/glad.o


shapegame.dylib: $(OBJS)
	$(CXX) -std=c++17 -dynamiclib -current_version 0.0.1 -compatibility_version 0.0.1\
	-undefined suppress -flat_namespace $(OBJS) -o $(MACOS_DIST_NAME)


obj/main.test.o:
	$(CXX) $(CXXFLAGS) $(INC_DIR) -c examples/main.test.cpp -o obj/main.test.o

obj/add-child-as.o:
	$(CXX) $(CXXFLAGS) $(INC_DIR) -c examples/add-child-as.cpp -o $@

$(OBJS): obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIR) -c $< -o $@

dist-mac: $(OBJS)
	$(CXX) $(INC_DIR) -std=c++17 -dynamiclib -current_version 0.0.1 -compatibility_version 0.0.1\
	 -undefined suppress -flat_namespace $(OBJS) -o $(MACOS_DIST_NAME)
	 mv $(MACOS_DIST_NAME) ./dist/mac

dist-linux: $(OBJS) $(GLAD)
	$(CXX) $(INC_DIR) -shared -undefined $(OBJS) -o $(LINUX_DIST_NAME)
	 mv $(LINUX_DIST_NAME) ./dist/linux

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(GLAD) bin/* obj/main.test.o $(EXE) $(MACOS_DIST_NAME) $(LINUX_DIST_NAME) $(WIN_DIST_NAME) *.o *.test
	@rm -rf *.dSYM
	@echo "Done cleaning"
