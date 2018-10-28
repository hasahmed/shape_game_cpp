UNAME := $(shell uname -s)
CXXFLAGS = -std=c++17 -g -Wall
SRC = $(wildcard *.test.cpp)
OBJS = $(SRC:.cpp=.o)
INC_DIR := -I../include
CXXFLAGS += $(INC_DIR)
ifeq ($(UNAME),Linux)
	CXX := c++
endif
ifeq ($(UNAME),Darwin)
	CXX := c++-7
endif


FileUtil:
	$(CXX) -o FileUtil ../FileUtil.cpp FileUtil.test.cpp $(INC_DIR) $(LDFLAGS)

# run: all
# 	./$(EXE)

# main: $(OBJS)
# 	$(CXX) -o $(EXE) $^ $(LDFLAGS)


.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf *.dSYM
	