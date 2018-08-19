CXX=c++-7
CXXFLAGS=-std=c++17
LINK.o = $(LINK.cc)

SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)
EXES=$(patsubst %.cpp,%,$(SRC))
DEPS_TMP=$(patsubst %.test.cpp,%.cpp,$(SRC))
DEPS=$(patsubst %,../%,$(DEPS_TMP))


all:
	@ruby compile.rb


#all: $(EXES)

#objs: $(OBJS)
	#$(CXX) -o  $^ $(DEPS)

#%.o : $(SRC)
	#$(CXX) $(CXXFLAGS) -c -o $@ $<

#$(DEPS):
	#$(CXX) $(CXXFLAGS) -c -o $@ $<



.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXES)
	@rm -rf *.dSYM
	@echo "Done cleaning"

